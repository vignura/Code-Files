import io.reactivex.Observable;
import io.reactivex.Flowable;
import io.reactivex.Single;
import io.reactivex.Completable;
import io.reactivex.Maybe;

public class TestRx {
   public static void main(String[] args) {
    Flowable.just("Flowable:", "1.Hello World!", "2.Hello World!", "").subscribe(System.out::println);
    Observable.just("Observable:", "1.Hello World!", "2.Hello World!", "").subscribe(System.out::println);
   	// the below line fails to compile as we are trying to emit two strings to
   	// System.out::println from a Single object !!
   	// Single.just("1.Hello World!", "2.Hello World!").subscribe(System.out::println);
   	Single.just("Single:\nHello World!").subscribe(System.out::println);
   	Maybe.just("MayBe:\nHello World!").subscribe(System.out::println);

   	// completable does not have just method !!
   	// Completable.just("Completable:\nHello World!").subscribe(System.out::println);

   }
}