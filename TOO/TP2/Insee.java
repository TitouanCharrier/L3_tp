
public class Insee {
  private long num;
  private long key;

  public Insee (long element1, long element2) {
    this.num = element1;
    this.key = element2;
  }

  public boolean check_length() {
    String num = Long.toString(this.num);
    String key = Long.toString(this.key);
    String regex_num = "\\d{13}$";
    String regex_key = "\\d{2}$";
    if (num.matches(regex_num) && key.matches(regex_key)) return true;
    else return false;
  }

  public boolean check_valid() {
    if (this.key == (97 - (this.num % 97))) return true;
    else return false;
  }

  public boolean check() {
    if (!this.check_length()) return false;
    if (!this.check_valid()) return false;
    
    else return true;
  }
}
