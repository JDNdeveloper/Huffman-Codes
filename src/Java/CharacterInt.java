/*
 * Huffman Code Project
 * CharacterInt.java
 * Purpose: Create data structure that stores
 *   a string, integer, and character
 *
 * @author Jayden Navarro
 * @version 1.0 4/20/13
 */
public class CharacterInt implements Comparable<CharacterInt> {
    private char ctr;
    private int num;
    private boolean composite;
    private CharacterInt left;
    private CharacterInt right;
    private String str;

    public CharacterInt(int num1, char ctr1) {
        composite = false;
        ctr = ctr1;
        num = num1;
    }

    public CharacterInt(String str1, char ctr1) {
        composite = false;
        ctr = ctr1;
        str = str1;
    }

    public CharacterInt(int num1, boolean comp1) {
        composite = comp1;
        ctr = '*';
        num = num1;
    }

    public int compareTo(CharacterInt CI) {
        return num - CI.getNumber();
    }

    public void setString(String str1) {
        str = str1;
    }

    public String getString() {
        return str;
    }

    public void setChar(char ctr1) {
        ctr = ctr1;
    }

    public void setNumber(int num1) {
        num = num1;
    }

    public void setIsComposite(boolean comp1) {
        composite = comp1;
    }

    public char getChar() {
        return ctr;
    }

    public int getNumber() {
        return num;
    }

    public boolean isComposite() {
        return composite;
    }

    public void setLeft(CharacterInt L) {
        left = L;
    }

    public void setRight(CharacterInt R) {
        right = R;
    }

    public CharacterInt getLeft() {
        return left;
    }

    public CharacterInt getRight() {
        return right;
    }

    public String toString() {
        String temp = "\'" + ctr + "\': " + num + ", String: " + str + "\n";
        return temp;
    }
}
