package gun;

public class Test {
    public static void main(String[] args) {
        Army army=new Army(4);
        Zhandouji zhandouji=new Zhandouji();
        Tanke tanke=new Tanke();
        Wuziji wuziji=new Wuziji();
        Gaoshepao gaoshepao=new Gaoshepao();
        try {
            army.addWeapon(zhandouji);
            army.addWeapon(tanke);
            army.addWeapon(wuziji);
            army.addWeapon(gaoshepao);
        }catch (AddWeaponExceptin e){
            System.out.println(e.getMessage());
        }
        army.moveAll();
        army.attack();
    }
}
