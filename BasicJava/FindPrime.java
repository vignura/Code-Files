import java.util.Scanner;
import java.lang.Math;

class FindPrime {
	public static void main(String[] args) {
		int iNum = 0;
		Scanner in = new Scanner(System.in);
		do{
			/* get user input */
			System.out.print("Enter number: ");
			iNum = in.nextInt();
			if(isPrime(iNum) == 1){
				System.out.println(iNum + " is a prime number");
			}
			else{
				System.out.println(iNum + " is not a prime number");
			}
		}while(1 != 0);
	}

	static int isPrime(int iNum){
		int iDiv = 2;
		/* handle negative numbers; 0 and 1 */
		if (iNum < 2) {
			return 0;
		}

		/* handle two and even numbers */
		if(iNum == 2)
		{
			return 1;
		}

		if((iNum % 2) == 0)
		{
			System.out.println("Divisor: 2");
			return 0;
		}

		for (iDiv = 3; iDiv <= Math.sqrt(iNum); iDiv += 2) {
			if((iNum % iDiv) == 0)
			{
				System.out.println("Divisor: " + iDiv);
				return 0;
			}
		}

		return 1;
	}
}