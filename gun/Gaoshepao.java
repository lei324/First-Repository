package gun;

public class Gaoshepao extends Weapon implements Shootable{
    @Override
    public void shoot() {
        System.out.println("高射炮发射炮弹");
    }
}
