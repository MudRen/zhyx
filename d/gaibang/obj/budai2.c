// budai.c ����

#include <armor.h>

inherit SHIELD;

static int amount;
private void destruct_me() { destruct(this_object()); }


void create()
{
        set_name("����", ({ "bu dai", "dai", "bag" }));
        set_weight(500);
        set_max_encumbrance(1000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("base_unit", "��");
                set("base_weight", 500);
                set("equiped",1);
                set("armor_prop/armor", 2); 
                        set("armor_prop/defense", 1); 

                set("long", "һֻ�ô��鲼֯�ɵĴ��ӣ��������������Ķ��٣���ؤ����ӽ�����λ�ı�־��\n");
                set("material", "cloth");
                set("base_armor", 5);
                set("no_drop", "��Ϊؤ����ӣ����������ڣ�������������\n");
                set("no_get",  "������������ذ��������ϣ����ò����֡�\n");
                set("no_steal", "������������ذ��������ϣ���͵�����֡�\n");
        }

        setup();
}

void init()
{
        add_action("do_remove", "remove");
}

int is_container() { return 1; }

int do_remove(string arg)
{
        if( (arg && present(arg, this_player()) == this_object())
          || arg == "all" ) {
                tell_object(this_player(), "ؤ����ӣ��������ڣ������������㲻�ܽ��������\n");
                return 1;
        }

        return 0;
}

