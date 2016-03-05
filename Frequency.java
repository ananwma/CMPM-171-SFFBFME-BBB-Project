import java.util.Scanner;
import java.io.File;

// program that finds how many times a string of size 2 occurs
// used in SFF to determine how many times a move strings to another move for melodic sounding combos
// Anan Ma 3/5/2016

public class Frequency{
	public static void find_frequency(String test_string){
		// pattern
		String str_arr[] = new String[100];
		// frequency
		int int_arr[] = new int[100];
		int size = 0;

		for(int i = 0; i<test_string.length()-1; i++){
			if(test_string.length() < 2){
				// string too short
				break;
			}
			else {
				if(str_arr[0] == null){
					str_arr[0] = test_string.substring(i, i+2);
					int_arr[0] = 1;
				}
				else if(test_string.substring(i,i+1).equals(" ") || test_string.substring(i+1,i+2).equals(" ")){
					// omit spaces
				}
				else{
					// check if substring already exists in the array
					boolean flag = false;
					for(int j=0; j<=size; j++){
						if(test_string.substring(i, i+2).equals(str_arr[j])){
							// if true, increment the frequency
							int_arr[j] = int_arr[j] + 1;
							flag = true;
							break;
						}
						else if((j==size) && (flag == false)){
							// if false, create it
							str_arr[size+1] = test_string.substring(i, i+2);
							int_arr[size+1] = 1;
							size++;
							break;
						}
					}
				}
			}
		}

		// sort from greatest frequency 
		int greatest = 0;
		int greatest_idx = 0;
		int sorted_int_arr[] = new int[100];
		String sorted_str_arr[] = new String[100];

		for(int sorted_size=0; sorted_size<=size; sorted_size++){
			for(int i = 0; i<=size; i++){
				if(int_arr[i]>greatest){
					greatest = int_arr[i];
					greatest_idx = i;
				}
				if(i==size){
					sorted_int_arr[sorted_size] = greatest;
					sorted_str_arr[sorted_size] = str_arr[greatest_idx];
					int_arr[greatest_idx] = -1;
					greatest = 0;
					greatest_idx = -1;
					break;
				}
			}
		}

		//print
		for(int i = 0; i<size+1; i++){
			System.out.println(sorted_str_arr[i] +" "+ sorted_int_arr[i]);
		}
	}
	public static void main(String[] args){
		// melodies / combos
		find_frequency("egcde gagfefg ccggaag gcccdee eeddc cccde geggeg ccdcfe ccdeced eefff gccdcbaaa gcdefgcc");
	/*
	Scanner input = new Scanner(System.in);
	while(input.hasNextLine()){
		String s1 = input.nextLine();
		find_frequency(s1);
	}
	input.close();*/
	}
}

