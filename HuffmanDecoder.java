import java.util.Arrays;
/*
 * Huffman Code Project
 * HuffmanDecoder.java
 * Purpose: Decodes Huffman Binary string
 *   using provided map
 *
 * @author Jayden Navarro
 * @version 1.0 4/20/13
 */
public class HuffmanDecoder {
    private String binary;
    private String decoded;
    private CharacterInt[] map;

    public String decode(String str, CharacterInt[] map1) {
        binary = str;
        map = map1;
        decoded = "";
        //System.out.println(Arrays.toString(map));
        //System.out.println(map.length);
        String tempString = "";
        int start = 0;
        for (int i = 0; i < binary.length(); i++) {
            int j = 0;
            tempString = binary.substring(start, i+1);
            for (; j < map.length; j++) {
                if (map[j].getString().equals(tempString)) {
                    break;
                }
            }
            if (j < map.length) {
                if (map[j].getString().equals(tempString)) {
                    decoded += map[j].getChar();
                    start = i+1;
                }
            }
        }
        return decoded;
    }
}
