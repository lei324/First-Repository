package gun;

public class Army {
    private Weapon[] weapons;

    public Army(int count) {
        this.weapons = new Weapon[count];
    }
    public void addWeapon(Weapon weapon) throws AddWeaponExceptin {
        for (int i = 0; i < weapons.length; i++) {
            if(null==weapons[i]){
                weapons[i]=weapon;
                return;
            }
        }
        throw new AddWeaponExceptin("武器已达上限");
    }
    public void attack(){
        for (int i = 0; i < weapons.length; i++) {
            if(weapons[i] instanceof Shootable){
                Shootable shootable=(Shootable) weapons[i];
                shootable.shoot();
            }
        }

    }
    public void moveAll(){
        for (int i = 0; i < weapons.length; i++) {
            if(weapons[i] instanceof Moveable){
                Moveable moveable=(Moveable) weapons[i];
                moveable.Moveable();
            }
        }
    }
}
