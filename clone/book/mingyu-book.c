// jiuyang.c

inherit ITEM;
inherit F_UNIQUE;
 
void create()
{
        set_name("�������񹦡�", ({ "mingyu shengong", "mingyu", "shengong" }));
        set_weight(500);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("long",
"����һ���������ܼ����������޵������µ������ؾ���\n",
        );
		set("value", 1);
		set("no_sell", 1);
                set("no_put", 1);
                set("no_give", 1);
                set("no_get", 1);
                set("material", "paper");
                set("skill", ([
                        "name"        : "mingyu-gong",
                        "exp_required":  100000,
                        "jing_cost"   :  120,
                        "difficulty"  :  40,
                        "max_skill"   :  400,
                ]) );
        }
}

int query_autoload() { return 1; }

