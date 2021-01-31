import java.util.concurrent.TimeUnit;

import io.reactivex.Completable;
import io.reactivex.disposables.Disposable;
import io.reactivex.observers.DisposableCompletableObserver;
import io.reactivex.schedulers.Schedulers;

public class ObservableTesterCompletable {
   public static void main(String[] args) throws InterruptedException {

      //Create an observer
      Disposable disposable = Completable.complete()
         .delay(2, TimeUnit.SECONDS, Schedulers.io())
         .subscribeWith(new DisposableCompletableObserver() {
         @Override
         public void onError(Throwable e) { 
            e.printStackTrace();
         }
         @Override
         public void onStart() {
            System.out.println("Started!");
         }
         @Override
         public void onComplete() {
            System.out.println("Done!");
         }
      }); 
      Thread.sleep(3000);
      //start observing
      disposable.dispose();
   }
}