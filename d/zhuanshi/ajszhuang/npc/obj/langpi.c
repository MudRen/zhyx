// langpi.c

inherit ITEM;

void create()
{
        set_name("��Ƥ", ({ "wolf skin", "skin" }));
        set_weight(3000);
        
        set("unit", "��");
        set("long", "����һ���ϵȵ�" + name() + 
                    "����ÿ����ɵ��ӡ�\n");
        set("value", 3000);
}

