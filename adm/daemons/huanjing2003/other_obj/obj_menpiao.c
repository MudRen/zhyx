//                ��׼��������ʾ��                                   |
// ��Ϸ����Ʊ
// by naihe  2002-11-03  ��ï��

inherit ITEM;

int query_autoload() { return 1; }

void create()
{
    set_name("���þ���ңԶ��˵֮��Ե���������֡� ����Ʊ", ({"men piao","piao"}));
    set_weight(10);
    if (clonep())
        set_default_object(__FILE__);
    else
    {
        set("long", "����һ�š��þ�����Ϸ���볡��Ʊ��ƾ��������볡��Ϸһ�Ρ�\n");
        set("unit", "��");
        set("value", 1);
        set("hj menpiao", 1);
    }

    setup();
}

