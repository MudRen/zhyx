//                ��׼��������ʾ��                                   |
// �þ�����Ʒ  ����ı���(������������б�)
// ����Ҫ������Ʒ�����ɻ��ҪѰ�ҵı��������Ҫ��ϲ��֣�
// by naihe  2002-10-28  ��ï��
// naihe 05-9-8 7:57 V1.8 �������¡�����һ��Ǳ��������

#include <ansi.h>

inherit ITEM;


string *names=({
    "��Ұ�屦��",
    "�����屦��",
    "�����屦��",
    "ɽ���屦��",
    "�����屦��",
});

string *ids=({
    "manye baowu",
    "mengli baowu",
    "aiyao baowu",
    "shanguai baowu",
    "juren baowu",
});

string *longs=({
    "����һ����Ұ��ı���ں�����һ�Ų�֪����ʲô��Ҳ��֪����ʲô�á�\n",
    "����һ��������ı���ں�����һ�Ų�֪����ʲô��Ҳ��֪����ʲô�á�\n",
    "����һ��������ı���ں�����һ�Ų�֪����ʲô��Ҳ��֪����ʲô�á�\n",
    "����һ��ɽ����ı���ں�����һ�Ų�֪����ʲô��Ҳ��֪����ʲô�á�\n",
    "����һ��������ı���ں�����һ�Ų�֪����ʲô��Ҳ��֪����ʲô�á�\n",
});

void setme( int iii )
{
    if( iii == 99 || iii < 0 || iii >= sizeof(names) )
        iii = random(sizeof(names));
    set("iii", iii);
    set_name( names[ iii ], ({ ids[ iii ], "baowu" }) );
    set_weight(100);
    if (clonep())
        set_default_object(__FILE__);

    set("long", longs[ iii ]);
    set("unit", "��");
    set("hj_game/obj","the_gem");
    set("no_refresh", 1); // ����MUDˢ��

    set("value", 1);  // ��������º󲻻���ʧ��
}

void create()
{
    setme(99);
    setup();
}
