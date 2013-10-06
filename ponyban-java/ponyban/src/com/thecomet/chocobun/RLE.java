/*
 * This file is part of Chocobun.
 *
 * Chocobun is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Chocobun is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Chocobun.  If not, see <http://www.gnu.org/licenses/>.
 */

package com.thecomet.chocobun;

/*!
 * @brief Simple RLE compression and decompression class
 *
 * @author Alex Murray (TheComet)
 *
 * <b>Run-length encoding (RLE)</b> is a very simple form of data compression
 * in which <i>runs</i> of data (that is, sequences in which the same data
 * value occurs in many consecutive data elements) are stored as a
 * single data value and count, rather than as the original run. This
 * is most useful on data that contains many such runs: for example,
 * simple graphic images such as icons, line drawings, and animations.
 * It is not useful with files that don't have many runs as it could
 * greatly increase the file size.
 *
 * <b>This implementationi supports two forms of RLE compression.</b>
 *
 * <b>Standard Compression</b> performs one pass on the data provided
 * and factors it accordingly. For example:
 * @code ####$$####$$####$$####$$ @endcode
 * becomes:
 * @code 4#2$4#2$4#2$4#2$ @endcode
 *
 * <b>Multi-pass Compression</b> performs as many passes as is required
 * to fully factor the string as far as possible. For example:
 * @code ####$$####$$####$$####$$ @endcode
 * becomes:
 * @code 4(4#2$) @endcode
 *
 */
public class RLE {

	/*!
	 * @brief Constructor
	 */
	public RLE() {
	}
	
	/*!
     * @brief Standard RLE compression
     * Performs one pass on the data provided and factors it accordingly. For example:
     * @code ####$$####$$####$$####$$ @endcode
     * becomes:
     * @code 4#2$4#2$4#2$4#2$ @endcode
     * @param str The string to compress
     * @return The compressed string
     */
	public String compress(String str) {
		
		// loop through all characters in the string
		String ret = "";
		int pos = 0;
		while( pos != str.length() ) {
			
			// loops until the current character doesn't match proceeding characters
	        int pos2 = pos+1;
	        while( pos2 != str.length() && str.charAt(pos) == str.charAt(pos2) ) ++pos2;
	        
	        // if more than one successive characters were found, apply RLE format
	        if( pos2 != pos+1 ) {
	            ret += (pos2-pos);
	        }
	        ret += str.charAt(pos);
	        pos = pos2;
	    }
	    return ret;
	}
	
	/*!
     * @brief Multi-pass RLE compression using parenthesis
     * Performs as many passes as is required to fully factor the string
     * as far as possible. For example:
     * @code ####$$####$$####$$####$$ @endcode
     * becomes:
     * @code 4(4#2$) @endcode
     * @param str The string to compress
     * @return The compressed string
     */
	public String multiPassCompress(String str) {
		
		// the same compression algorithm is performed twice,
	    // one time factoring from the outside in and the other
	    // time factoring from the inside out. The two are compared
	    // and the best result is returned.
	    String method1;
	    String method2;

	    // the compare size is the number of characters to compare with the
	    // rest of the string to find matching patterns
	    method1 = str;
	    for( int compareSize = 1; compareSize < str.length()/2; ++compareSize ) {
	        method1 = this.multPassCompress_pass( compareSize, method1 );
	    }
	    method2 = str;
	    for( int compareSize = str.length()/2; compareSize > 0; --compareSize ) {
	        method2 = this.multPassCompress_pass( compareSize, method2 );
	    }

	    // compare length to determine which one was more successful
	    if( method1.length() < method2.length() )
	    	return method1;
	    else
	    	return method2;
	}
	
	/*!
     * @brief Passes an entire string, factoring out sections with the length of compareSize
     *
     * @param compareSize The length of the sections to factor out
     * @param input The input string
     * @param output The output string
     *
     * @note This is used internally by the multi-pass compression method
     */
    private String multPassCompress_pass( int compareSize, String input ) {
    	
    	String ret = "";
    	
    	// loops through all characters in the string with a step size
        // of the compare size
        int pos = 0;
        while( pos <= input.length() )
        {

            // the compare string
        	int pos_end = pos+compareSize;
        	if(pos_end > input.length() )
        		pos_end = input.length();
            String compare = input.substring(pos, pos_end);

            // loops until the compare pattern doesn't repeat any more
            int pos2 = pos+compareSize;
            int pos2_end = pos2+compareSize;
            if(pos2_end > input.length() )
            	pos2_end = input.length();
            while( pos2 <= input.length() && input.substring(pos2, pos2_end).compareTo(compare) == 0 ) {
            	pos2 += compareSize;
            	pos2_end += compareSize;
            	if( pos2_end > input.length() )
            		pos2_end = input.length();
            }

            // if a pattern was found, apply RLE formatting
            if( pos2 != pos+compareSize )
            {
                ret += ((pos2-pos) / compareSize);
                if( compareSize != 1 )
                {
                    ret += '(';
                    ret += compare;
                    ret += ')';
                }else
                    ret += compare;
            }

            // if no patter was found, simply append the compare pattern
            else
                ret += compare;

            pos = pos2;
        }
        
        return ret;
    }
	
	/*!
     * @brief RLE Decompression
     * @note Supports multi-pass and standard compression
     * @param str The string to decompress
     * @return The decompressed string
     */
	public String decompress(String str) {
		StringBuilder ret = new StringBuilder(str);
		this.decompress_recursive(ret);
		return ret.toString();
	}
	
	/*!
	 * @brief RLE Decompression recursive implementatin
	 * @note A StringBuilder object is passed as the argument instead of a
	 * string in order to allow the function to modify the original object.
	 * @return A position relative to the string's beginning
     * where the last refactor occurred. You may ignore this and simply call
     * the method without catching the return value; it's used internally.
	 */
	private int decompress_recursive(StringBuilder str) {
		
		String ret = "";
	    int pos = 0;
	    while( pos < str.length() )
	    {

	        // closing parenthesis
	        if( str.charAt(pos) == ')' ) break;

	        // get expansion
	        int expansionCount = 0, digit = 1;
	        while( str.substring(pos,pos+1).matches("[0-9]") )
	        {
	            expansionCount *= digit;
	            expansionCount += str.charAt(pos)-48;
	            digit *= 10;
	            ++pos;
	        }
	        if( digit == 1 ) expansionCount = 1;

	        // get string to expand
	        StringBuilder expansionString = new StringBuilder();
	        if( str.charAt(pos) == '(' )
	        {
	            expansionString.append( str.substring(pos+1,str.length()) ); // +1 to skip opening parenthesis
	            pos += this.decompress_recursive( expansionString );
	        }
	        else
	            expansionString.append( str.charAt(pos) );

	        // expand
	        for( int i = 0; i != expansionCount; ++i ) {
	            ret += expansionString;
	        }
	        ++pos;
	    }
	    str.setLength(0);
	    str.append(ret);
	    return pos+1; // +1 to skip closing parenthesis
	}
    
	/* test code
    public static void main( String[] args ) {
    	RLE rle = new RLE();
    	String test = "####$$$$####$$$$";
    	String c1 = rle.compress(test);
    	String c2 = rle.decompress(c1);
    	String c3 = rle.multiPassCompress(c2);
    	String c4 = rle.decompress(c3);
    	System.out.println("Input string: " + test);
    	System.out.println("single pass compress: " + c1);
    	System.out.println("decompress: " + c2);
    	System.out.println("multi pass compress: " + c3);
    	System.out.println("decompress: " + c4);
    }*/
}
