package drugs;

import bash_test.Solider;

public class Xanax {
	
	public void heal(Solider s) {
		
		if(s.health < 100 ) {
			s.health = 100;
			
		}
		
	}

}
