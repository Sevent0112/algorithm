package class01;

public class Code06_PrintB {

    public static void print(int num){
        for(int i = 31; i >=0; i--) {
            System.out.print((num & (1<<i)) == 0? "0" : "1");

        }
        System.out.print('\n');
    }


    public static void main(String[] args){
        int num = -7433894;
        int a = Integer.MIN_VALUE;
        print(~a);
        print(a);
        System.out.println();


    }
}
