// bijini.c

inherit EQUIP;

void create()
{
        set_name("�Ȼ���Ӿ��", ({ "bijini", "cloth", }) );
        set("long","����һ�������Ӿװ�����������Ծ���Ů�Ե���������\n");
        set_weight(200);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("armor_type", "cloth");
                set("value", 2500);
                set("no_get",1);
                set("no_put",1);
                set("only_do_effect",1);
                set("armor_prop/dodge", 6);
                set("armor_prop/armor", 1);
        }
}

