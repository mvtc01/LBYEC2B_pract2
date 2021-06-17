#include <iostream>

#define healAmount 15
#define buffAttackAmount 10
#define buffDefenseAmount 5

using namespace std;

class Character
{
private:
    int vitality;
    int attack;
    int defense;

public:
    //Constructor
    Character(int a, int b, int c)
    {
        vitality = a;
        attack = b;
        defense = c;
    }

    //Setter
    void setVitality(int x)
    {
        vitality = x;
    }
    void setAttack(int x)
    {
        attack = x;
    }
    void setDefense(int x)
    {
        defense = x;
    }

    //Getter
    int getVitality()
    {
        return vitality;
    }
    int getAttack()
    {
        return attack;
    }
    int getDefense()
    {
        return defense;
    }

    void showStats()
    {
        cout << "\tVitality Rating: " << vitality << "\n";
        cout << "\tAttack Rating: " << attack << "\n";
        cout << "\tDefense Rating: " << defense << "\n";
    }
};

class Player : public Character
{
public:
    //Constructor
    Player(int a, int b, int c) : Character(a, b, c)
    {
    }

    void healUp(int x)
    {
        //-----------------------------------------------------------------------------------------------
        // -> increase the vitality of the hero by x
        //INSERT CODE HERE - START
		x += getVitality();
		setVitality(x);
        //INSERT CODE HERE - END
        //-----------------------------------------------------------------------------------------------
    }

    void buffWeapon(int x)
    {
        //-----------------------------------------------------------------------------------------------
        // -> increase the attack of the hero by x
        //INSERT CODE HERE - START
		x += getAttack();
		setAttack(x);
        //INSERT CODE HERE - END 
        //-----------------------------------------------------------------------------------------------
    }

    void buffArmor(int x)
    {
        //-----------------------------------------------------------------------------------------------
        // -> increase the defense of the hero by x
        //INSERT CODE HERE - START
		x += getDefense();
		setDefense(x);
        //INSERT CODE HERE - END
        //-----------------------------------------------------------------------------------------------
    }
};

int main()
{
    Player hero(30, 5, 0);         //30 starting hp, 5 starting attack, 0 starting defense
    Character monster(30, 10, 10); //30 starting hp, 10 starting attack, 10 starting defense

    int i, action, damage;

    cout << "Welcome to the LBYEC2B Practical Exam 2 Adventure Game"
         << "\n";

    while (hero.getVitality() > 0 || monster.getVitality() > 0)
    {
        cout << "Hero Stats:\n";
        hero.showStats();
        cout << "\nMonster Stats:\n";
        monster.showStats();
        cout << "\nAvailable actions:\n";
        cout << "\t(1) Attack Monster\n"
             << "\t(2) Heal Up\n"
             << "\t(3) Buff Weapon\n"
             << "\t(4) Buff Armor\n";
        cout << "Choose Action: ";
        cin >> action;

        switch (action)
        {
        case 1:
            //-------------------------------------------------------------------------------------------
            // -> reduces the vitality of the monster by 'damage'
            // -> 'damage' is calculated by subtracting the monster's defense from the hero's attack
            // -> if the negative computed 'damage' is negative, it should be set to zero
            //INSERT CODE HERE - START
				damage = hero.getAttack() - monster.getDefense();
				if (damage < 0) 
					damage = 0;
				i = monster.getVitality() - damage;	
				monster.setVitality(i);
            //INSERT CODE HERE - END
            //-------------------------------------------------------------------------------------------
            cout << "The hero deals " << damage << " damage to the monster!\n";
            break;
        case 2:
            //-------------------------------------------------------------------------------------------
            // -> calls the correct method and increases the vitality of the hero by 'healAmount'
            //INSERT CODE HERE - START
			hero.healUp(healAmount);
            //INSERT CODE HERE - END
            //-------------------------------------------------------------------------------------------
            cout << "The hero heals " << healAmount << " hp!\n";
            break;
        case 3:
            //-------------------------------------------------------------------------------------------
            // -> calls the correct method and increases the attack of the hero by 'buffAttackAmount'
            //INSERT CODE HERE - START
			hero.buffWeapon(buffAttackAmount);
            //INSERT CODE HERE - END
            //-------------------------------------------------------------------------------------------
            cout << "The hero's attack increased by " << buffAttackAmount << " points!\n";
            break;
        case 4:
            //-------------------------------------------------------------------------------------------
            // -> calls the correct method and increases the defense of the hero by 'buffDefenseAmount'
            //INSERT CODE HERE - START
			hero.buffArmor(buffDefenseAmount);
            //INSERT CODE HERE - END
            //-------------------------------------------------------------------------------------------
            cout << "The hero's defense increased by " << buffDefenseAmount << " points!\n";
            break;
        default:
            cout << "The hero skips his turn!"
                 << "\n";
            break;
        }
        //---------------------------------------------------------------------------------------------------
        // -> reduces the vitality of the hero by 'damage'
        // -> 'damage' is calculated by subtracting the hero's defense from the monster's attack
        // -> if the negative computed 'damage' is negative, it should be set to zero
        //INSERT CODE HERE - START
		damage = monster.getAttack() - hero.getDefense();
		if (damage < 0) 
			damage = 0;
		i = hero.getVitality() - damage;	
		hero.setVitality(i);
        //INSERT CODE HERE - END
        //---------------------------------------------------------------------------------------------------
        cout << "The monster deals " << damage << " damage to the hero!\n";

        if (monster.getVitality() <= 0 && hero.getVitality() <= 0)
        {
            cout << "\nThe battle ended in a DRAW!";
            return 0;
        }
        else if (monster.getVitality() == 0 && hero.getVitality() > 0)
        {
            cout << "\nThe hero WINS the battle!";
            return 0;
        }
        else if (monster.getVitality() > 0 && hero.getVitality() == 0)
        {
            cout << "\nThe hero LOSES the battle!";
            return 0;
        }
    }
}
