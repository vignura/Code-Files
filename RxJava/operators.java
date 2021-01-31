import io.reactivex.Observable;
//Using fromArray operator to create an Observable
public class operators {
	public static void main(String[] args) { 

		String[] letters = {"a", "b", "c", "d", "e", "f", "g"};
		final StringBuilder result = new StringBuilder();

		Observable<String> observable = Observable.fromArray(letters);
		observable
		.map(String::toUpperCase)
		.subscribe( letter -> result.append(letter));
		// .subscribe(System.out.println);
		System.out.println(result);

		// creating an observable from scratch
		Observable.create(emitter -> {
			emitter.onNext("Hello World");
			emitter.onComplete();
		}).subscribe(s -> System.out.println(s));
	}
}