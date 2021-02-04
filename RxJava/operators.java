import io.reactivex.Observable;
import io.reactivex.Completable;
import io.reactivex.CompletableObserver;
import io.reactivex.disposables.Disposable;
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


		// creating an observable from scratch
		Observable.create(emitter -> {
			for (int i = 0; i < 10; i++) {
				emitter.onNext("num: " + String.valueOf(i));
			}	
			emitter.onComplete();
		}).subscribe(s -> System.out.println(s));


		// creating an completable
		Completable.create(emitter -> {
			// do some task and then emit completed signal
			if(false){
			// if(true){
				emitter.onComplete();
			}
			else{
				Throwable e = new Throwable("error");
				emitter.onError(e);
			}			
		}).subscribe(new CompletableObserver(){
			public void onSubscribe(Disposable d)
			{
				System.out.println("subscribed");
			}
			public void onComplete()
			{
				System.out.println("success: completed");
			}
			public void onError(Throwable e){
				System.out.println("failure: "+e.getMessage());
			}
		});
	}
}