
//���е�
//lestat for �ε���
#include <weapon.h>
inherit SWORD;
void create()
{
        set_name("���е�", ({"niren dao", "sword", "dao",
"nirendao"}));
        set_weight(100);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long","�⿴��ȥ����һ�ѵ�����ֵ��ǵ��о�Ȼ�Ƿ��ġ�\n");
                set("unit", "��");
		set("wield_msg",
"$n��ৡ��شӽ����е���������$N�����С�\n");
		set("unwield_msg",
"$N�����е�$n�������䣬��ɫ���������ˣ�\n");
                set("value", 0);
           set("badao", 1);
		set("weapon_prop/courage", 10);
        }
        init_sword(1);
        setup();
}
