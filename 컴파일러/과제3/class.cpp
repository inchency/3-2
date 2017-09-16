class Account {
      int account_number;
      double balance;

      Account (int account, double initial) {
         account_number = account;
         balance = initial;
      }  // constructor Account

      void deposit (double amount) {
         balance = balance + amount;
      }  // method deposit

}  // class Account
