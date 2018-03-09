package bash_test;

public class Weapon {
	
	int dmg;
	
	public Weapon() {
		dmg = 75;
	}
	
	void weaponsound() {
		System.out.println("Duuuurrrrrrr");
	}
	
	void shot(Solider s, Solider e) {
		this.dmg *= s.attack_power;
		e.health -= this.dmg;
		weaponsound();
		System.out.println("Durrmárheee");
		
	}

}
