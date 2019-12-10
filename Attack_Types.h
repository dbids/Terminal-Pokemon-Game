#ifndef ATTACK_TYPES
#define ATTACK_TYPES
class Attack_Types
{
    public:
        Attack_Types();
        Attack_Types(std::string& in_name);
        Attack_Types(std::string& in_name, double in_mag_dmg, double in_phy_dmg);

        double getPhyDamage();
        double getMagDamage();
        std::string getName();

        void levelUp();

        void printAttack();
    private:
        std::string name;
        double physical_damage;
        double magical_damage;
};
#endif
