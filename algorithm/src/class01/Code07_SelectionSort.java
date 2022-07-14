package class01;

public class Code07_SelectionSort {

    public static void SelectSort(int[] arr) {
        // my code
//        if (arr == null || arr.length <2)
//            return;
//        for (int i = 0; i < arr.length - 1; i++) {
//            int min_value = i;
//            int temp = arr[i];
//            for (int j = i; j < arr.length ; j++)
//               min_value =  arr[j] < arr[min_value]? j:min_value;
//            arr[i] = arr[min_value];
//            arr[min_value] = temp;
//        }
    // code from course
        if (arr == null || arr.length<2)
            return;
        int N = arr.length;
        for (int i = 0; i < N; i++) {
            int minValueIndex = i;
            for (int j = i + 1; j < N; j++) {
                minValueIndex = arr[minValueIndex] > arr[j] ? j : minValueIndex;
            }
            swap(arr, i, minValueIndex);
        }
    }

    public static void swap(int[] arr, int i, int j)    {
        int tmp = arr[i];
        arr[i] = arr[j];
        arr[j] = tmp;
    }
    public static void printArray(int[] arr) {
        for (int j : arr) System.out.print(j + " ");
        System.out.println();
    }


    public static void main(String[] args){
        int[] arr = {4,3,6,7,43,23,6,8};
        SelectSort(arr);
        printArray(arr);

    }
}
