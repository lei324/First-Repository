package gun;

public class Tanke extends Weapon implements Moveable,Shootable{
    @Override
    public void Moveable() {
        System.out.println("坦克移动");
    }

    @Override
    public void shoot() {
        System.out.println("坦克开炮");
    }
}
