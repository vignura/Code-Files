import java.util.concurrent.TimeUnit;

import io.reactivex.Single;
import io.reactivex.disposables.Disposable;
import io.reactivex.observers.DisposableSingleObserver;
import io.reactivex.schedulers.Schedulers;

public class ObservableTester  {
   public static void main(String[] args)  throws InterruptedException {
      //Create the observable
      Single<String> testSingle = Single.just("Hello World");

      //Create an observer
      Disposable disposable = testSingle
         .delay(10, TimeUnit.SECONDS, Schedulers.io())
         .subscribeWith(
         new DisposableSingleObserver<String>() {

         @Override
         public void onError(Throwable e) { 
            e.printStackTrace();
         }

         @Override
         public void onSuccess(String value) {
            System.out.println(value);
         }
      }); 
      Thread.sleep(30000);
      //start observing
      disposable.dispose();
   }
}