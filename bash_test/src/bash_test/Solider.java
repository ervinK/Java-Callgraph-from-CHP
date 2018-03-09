package bash_test;

import drugs.Xanax;

public class Solider {
	
	public String name;
	public int health;
	public int attack_power;
	public Weapon w;
	
	public Solider(String n, int h, int a_p, Weapon w) {
		
		this.name = n;
		this.health = h;
		this.attack_power = a_p;
		this.w = w;
		
	}
	
	void attack(int a_p, Solider e) {
		w.shot(this, e);
		System.out.println("Whooooaaa!");
		
	}
	
	void healWithPill() {
		Xanax x1 = new Xanax();
		x1.heal(this);
	}
	

}
