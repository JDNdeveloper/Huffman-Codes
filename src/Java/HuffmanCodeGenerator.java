import java.util.ArrayList;
import java.util.Arrays;
import java.lang.Character;
/*
 * Huffman Code Project
 * HuffmanCodeGenerator.java
 * Purpose: Creates Huffman Binary Strings
 *    using a given String
 *
 * @author Jayden Navarro
 * @version 1.0 4/20/13
 */
public class HuffmanCodeGenerator {
    private String original;
    private String converted;
    private ArrayList<CharacterInt> frequency;
    private CharacterInt[] map;
    private String[] quickMap;

    private int[] ascii;
    private CharacterInt[] elements;
    private CharacterInt top;

    public HuffmanCodeGenerator() {
        original = "";
        converted = "";
        frequency = new ArrayList<CharacterInt>();
    }

    public String generate(String str) {
        //Clear
        frequency.clear();
        ascii = new int[256];
        original = "";
        converted = "";

        original = str;
        countFrequency();
        //System.out.println(Arrays.toString(elements));
        Arrays.sort(elements);
        //System.out.println(Arrays.toString(elements));
        createTree();
        map = new CharacterInt[elements.length];
        quickMap = new String[256];
        createMap("", top);
        int j = 0;
        for (int i = 0; i < quickMap.length; i++) {
            String str1 = quickMap[i];
            char ctr = (char) i;
            if (str1 != null && j < elements.length) {
                CharacterInt temp = new CharacterInt(str1, ctr);
                map[j] = temp;
                j++;
            }
        }
        convertString();

        return converted;
    }

    private void convertString() {
        for (int i = 0; i < original.length(); i++) {
            converted += quickMap[original.charAt(i)];
        }
    }

    public String getBinary() {
        return converted;
    }

    public String getOriginal() {
        return original;
    }

    public CharacterInt getTop() {
        return top;
    }

    private void createMap(String bin, CharacterInt m) {
        CharacterInt tempLeft;
        CharacterInt tempRight;
        CharacterInt tempMain = m;
        if (tempMain.isComposite()) {
            tempLeft = tempMain.getLeft();
            tempRight = tempMain.getRight();
            String binLeft = bin + '0';
            String binRight = bin + '1';
            createMap(binLeft, tempLeft);
            createMap(binRight, tempRight);
        } else {
            CharacterInt tempCI = new CharacterInt(bin, m.getChar());
            quickMap[tempCI.getChar()] = tempCI.getString();
        }
    }

    private void countFrequency() {
        for (int i = 0; i < original.length(); i++) {
            ascii[original.charAt(i)]++;
        }
        for (int i = 0; i < ascii.length; i++) {
            int num = ascii[i];
            char ctr = (char) i;
            if (num != 0) {
                CharacterInt temp = new CharacterInt(num, ctr);
                frequency.add(temp);
            }
        }
        elements = new CharacterInt[frequency.size()];
        elements = frequency.toArray(elements);
    }

    public CharacterInt[] getMap() {
        return map;
    }

    public String[] getQuickMap() {
        return quickMap;
    }

    private void createTree() {
        for (int i = 1; i < elements.length; i++) {
            int total = elements[i].getNumber() + elements[i-1].getNumber();
            CharacterInt tempCI = new CharacterInt(total, true);
            tempCI.setLeft(elements[i-1]);
            tempCI.setRight(elements[i]);
            elements[i] = tempCI;
            Arrays.sort(elements, i, elements.length);
        }
        top = elements[elements.length-1];
    }

    public String getMapAsString() {
        String temp = "";
        for (int i = 0; i < map.length; i++) {
            temp += "\'" + map[i].getChar() + "\': " + map[i].getString() + "\n";
        }
        return temp;
    }
}
