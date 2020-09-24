 use std::io;
 use std::io::Write;
 
 fn main() {
 	print!("Enter a number: ");
 	io::stdout().flush().unwrap();

 	let mut line = String::new();
 	io::stdin().read_line(&mut line).unwrap();
 	let num: i32 = line.trim().parse().unwrap();

 	if is_prime(num) {
 		println!("{} is a prime number", num);
 	}
 	else {
 		println!("{} is not a prime number", num);
 	}
 }

 fn is_prime(num: i32) -> bool{
 	let lim: i32 = ((num as f32).sqrt()) as i32;
	let _div: i32;

	/* handle negative numbers; 0 and 1 */
	// println!("1:");
	if num < 2 {
		return false;
	}

	// println!("2:");
	/* handle two and even numbers */
	if num == 2 {
		return true;
	}

	// println!("3:");
	if(num % 2) == 0 {
		println!("Divisor: 2");
		return false;
	}

	// println!("4:");
	for div in 3 .. (lim + 1) {
		if(num % div) == 0 {
			println!("Divisor: {}", div);
			return false;
		}
	}

	// println!("5:");
	return true;
 }