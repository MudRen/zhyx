// chess book.c

inherit ITEM;

void create()
{
        set_name("��������", ({ "chess book", "book" }));
        set_weight(600);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("long",
"������д�����������ţ���\n");
                set("value", 1000000);
                set("material", "paper");
                set("skill", ([
                        "name":         "chess",
                        "exp_required": 1000000,
                        "jing_cost":    100,
                        "difficulty":   100,
                        "max_skill":    199,
                ]));
        }
}

