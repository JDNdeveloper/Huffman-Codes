import java.util.Arrays;
/*
 * Huffman Code Project
 * HuffmanCodesMain.java
 * Purpose: Tests Huffman Code Classes
 *
 * @author Jayden Navarro
 * @version 1.0 4/20/13
 */
public class HuffmanCodesMain {
    public static void main(String[] args) {
        HuffmanCodeGenerator HCG = new HuffmanCodeGenerator();
        HuffmanDecoder HD = new HuffmanDecoder();

        String original = "aaaabbbbbbbccccccccccddddeeeffffffg";

        System.out.println("Original: " + original + "\n");

        System.out.println("Binary:");
        System.out.println(HCG.generate(original) + "\n");

        System.out.println("Binary Values Map:");
        System.out.println(HCG.getMapAsString());

        System.out.println("Decoded:");
        System.out.println(HD.decode(HCG.getBinary(), HCG.getMap()));
    }
}
