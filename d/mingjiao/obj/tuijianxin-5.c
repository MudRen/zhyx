// tuijianxin-5.c �Ƽ��� ��-ʹ��

inherit ITEM;

void create()
{
        set_name("�Ƽ���", ({"tuijian xin5", "xin4", "letter5"}));
        set_weight(100);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("long","����һ�⻤�̷���Ϊ��д���Ƽ��ţ�ƾ�˿�ȥ������ʹ�ߡ�\n");
                set("material", "paper");
        }
}

