package class01;

public class Code01_SumOfFactorial {

    public static long f1(int N ) {
        long ans = 0;
        for (int i = 1; i<= N; i++) {
            ans += factorial(i);
        }
        return ans;
    }

    public static long factorial(int N) {
        long ans = 1;
        for (int i = 1; i <= N; i++)    {
            ans *= i;
        }
        return ans;
    }

    public static long f2(int N) {
        long ans = 0;
        long temp = 1;
        for (int i = 1; i<=N ; i++) {
            temp = temp * i;
            ans += temp;
        }
        return ans;
    }

    public static void main(String[] args){
        int n = 4;
        System.out.println(f2(n));
        System.out.println(f1(n));
    }
}
