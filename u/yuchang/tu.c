// tu.c BY YUCHANG

#include <ansi.h>
inherit ITEM;
inherit F_AUTOLOAD;
void create()
{
        set_name(HIB"�ر�ͼ"NOR, ({"bao tu","baotu"}) );
        set_weight(10);
        set("no_steal", 1);
        set("no_beg", 1);
        set("no_sell", 1);
//        set("no_get", 1);
        set("no_drop","�ۣ��ر�ͼ���붪��,С������Ǵ��\n\n");
        set("long",@LONG
���˵����۰����µı���ͼ,�쿴��(kan)�ɣ�
LONG );
        if( clonep() )
                        set_default_object(__FILE__);
        else
       {
                set("unit", "��");
                set("material", "unknow");
        }
}

void init()
{
        add_action( "kan_tu", "kan tu" );
}

int query_autoload()
{
        return 1;
}
//����
int kan_tu()
{
        object me;
        me=this_player();
        tell_object(me,
    "��˵�еľ����ý������嵱ɽ�ϣ�\n");
        return 1;
}




