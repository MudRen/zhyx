//xdh_guard.c

inherit NPC;

#include <ansi.h>

int ask_xdh(object me, object ob);
void create()
{
        set_name("����",({"shou wei","guard"}) );
        set("long","����һ�������ˣ��������������ġ�\n");
        set("title","С�������");
        set("gender","����");
        set("age",20);
        set("combat_exp",100);
        set("inquiry",([
                "С����" : (: ask_xdh :),
                ]) );
        setup();
}

int ask_xdh(object me, object ob)
{
        
        me=this_player();
        ob=this_object();
        if (me->query("bang_bad/name")!="С����")
        {
                command("grin");
                tell_object(me,"С��������˵��������Ͷ������С����ɣ��Ǿ͵��ع�ء���\n");
                tell_object(me,HIB"С���������úڲ���������۾������������߰��ߣ���������һ
���������档\n�����ŵĺڲ�Ҳ����ȡ��������\n"NOR);
                tell_room("$N�����˽�����\n",me);
                me->move("/d/city/xdhzb");
                return 1;
        }
        if( me->query("bang_good"))
        {
                command("say ����С���᲻��ӭ�������������ɵ��ˣ���ذɡ�\n");
                return 1;
        }
        
        tell_object(me,"С����������ֵ�����ͬΪ�����ֵܣ���γ����԰�����\n");
        return 1;
}

        
