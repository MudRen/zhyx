#include <ansi.h>
inherit ITEM;

string do_long();
string name,id;
int birthday;

void create()
{
        object me = this_player();
        name = me->query("name");
        id = me->query("id");
        birthday = me->query("birthday");
        set_name("���ӱ�", ({ "watch" }) );
        set("long", (: do_long :) );
        set("unit", "��");
        set("value", 0);

        setup();
}

int query_autoload()
{
        if( id != this_player()->query("id") ) return 0;
        return 1;
}

void init()
{
        add_action("do_zeng", "zeng");
}

int do_zeng(string arg)
{
        object me, ob, obj;
        string item, target;;

        me = this_player();
        if(!arg||sscanf(arg, "%s to %s", item, target)!=2) return notify_fail("zeng <��Ʒ> to <ĳ��>\n");
        obj = present(item, me);
        ob = present(target, environment(me));
        if(!ob) return notify_fail("����û������ˡ�\n");
        if(!obj) return notify_fail("������û��������Ʒ��\n");
        if(obj!=this_object()) return notify_fail("�����������ǲ����ĺá�\n");
        if( id!=me->query("id") ) return notify_fail("�㲻�������Ʒ�����ˣ���Ȩת����\n");
        name = ob->query("name");
        id = ob->query("id");
        birthday = ob->query("birthday");
        obj->move(ob);
        if( me->query("id") == "wop" ) message_vision("$N����$nһ" + obj->query("unit") + obj->query("name") +"��\n", me, ob);
        else message_vision("$N��" + obj->query("name") + "ת������$n��\n", me, ob);
        return 1;
}

string do_long()
{
        mixed *local, *birth;
        string ld,lt,gt;
        int h, y;

        local = localtime(time());
        ld = sprintf("%d-%s%d-%s%d", local[5],
                (local[4]<9)?"0":"", local[4]+1,
                (local[3]<10)?"0":"", local[3]);
        h = (local[2]>12)?(local[2]-12):local[2];
        lt = sprintf("%s%d:%s%d:%s%d%s", (h<10)?"0":"", h,
                (local[1]<10)?"0":"", local[1],
                (local[0]<10)?"0":"", local[0],
                (local[2]>12)?"pm":"am"
                );

        birth = localtime(birthday);
        if( (local[4]>birth[4]) || ((local[4]==birth[4])&&(local[3]>=birth[3])) )
                y = local[5];
        else y = local[5] - 1; 
        gt = CHINESE_D->chinese_number(y/1000) + CHINESE_D->chinese_number((y/100)%10)
                + CHINESE_D->chinese_number((y/10)%10) + CHINESE_D->chinese_number(y%10)
                + "��" + CHINESE_D->chinese_number(birth[4]+1) + "��"
                + CHINESE_D->chinese_number(birth[3]) + "��";

        printf("����һ�龫�µĵ��ӱ�������ʾ���ڵ�ʱ���ǣ�\n\n");
        printf(HIY"\t\t"HBBLU"������������������\n"NOR);
        printf(HIY"\t\t"HBBLU"��  "HIR"%s"YEL"  ��\n"NOR, ld);
        printf(HIY"\t\t"HBBLU"��  "HIR"%s"YEL"  ��\n"NOR, lt);
        printf(HIY"\t\t"HBBLU"������������������\n"NOR);
        printf("\n��ı������һ��С�֣�\n\n");
        printf(HIY"\t��%s��\n\n"NOR, name);
        printf(HIR"\t\tף�������!\n\n"NOR);
        printf(HIB"\t\t\t\t\tҹ��(nightstar)����\n"NOR);
        printf(HIB"\t\t\t\t\t%s\n"NOR, gt);
        return "";
}
