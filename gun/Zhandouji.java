package gun;

public class Zhandouji extends Weapon implements Moveable,Shootable{
    @Override
    public void Moveable() {
        System.out.println("战斗机起飞");
    }

    @Override
    public void shoot() {
        System.out.println("战斗机发射");
    }
}
