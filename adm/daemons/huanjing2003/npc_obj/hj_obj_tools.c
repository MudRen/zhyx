//                ��׼��������ʾ��                                   |
// �þ�����Ʒ  ��Ϸ��������
// by naihe  2002-10-24 ~ 25  ��ï��
// ����һ�� fx, dx, xr ��Ч�� 05-8-31 10:16

#include <ansi.h>

inherit ITEM;

#include "hj_settings/obj_list.h"          // ���嶨��ı�����ο����ļ�
#include "hj_settings/room_amount_hj.h"

string *names=({
    HIG"����ˮ��"NOR,
    HIC"����֮ʯ"NOR,
    YEL"����ˮ��"NOR,
    HIW"�ع�֮��"NOR,
    HIY"��֮ʯ"NOR,
    HIM"�ٻ�֮��"NOR,
    HIM"����֮��"NOR,
    HIM"����֮��"NOR,
    HIG"Ѱ��ˮ��"NOR,
    HIB"��̽ˮ��"NOR,
    HIW"��λ֮��"NOR,
});

/************************************
 �������������뷨������
1������̫�࣬��ҽ������ʴ�
2��ÿ���뵽�µĶ�Ҫ��ӣ���ʱ���Ǹ�ͷ��
3��һЩ��ǿ���ĵ��ߣ������� �þ�ϵ�� ��2�� ��д��

by the way, ��2�����������ü������ȵĹ�˼�ˣ�
��ҽ��ܹ���һ��������Ϸ��ȥ������������1����
�Ĺ��£�����

���ң���2���ｫ�������Ϊ�������ݣ����
��Ŀ�Դ�һ����һ�㡢ʷʫһ�����ڰɣ�

YEAH~~   all by naihe 2002-10 ~ 11

����δд������ naihe 14:04 03-10-15
**************************************/



string *ids=({
    "dx shuijing",
    "fx zhishi",
    "tl shuijing",
    "hg zhijing",
    "qd zhishi",
    "zh zhihe",
    "fd zhiqi",
    "qz zhiqi",
    "xr shuijing",
    "kt shuijing",
    "dw zhiyi",
});

string *ids2=({
    "shj",
    "shi",
    "shj",
    "jing",
    "shi",
    "he",
    "qi",
    "qi",
    "shj",
    "shj",
    "yi",
});

string *longs=({
    "����һ������ˮ�������������(dingxiang / dx)����Լ����ںδ���\n",
    "����һ�ŷ���֮ʯ�����������(feixiang / fx)˲����赽�þ�����κεط���\n",
    "����һ������ˮ�������������(tuoli / tl)�ӿ�����������ȥ����ĵط���\n",
    "����һ��ع�֮�������������(huigui / hg)�����뿪�þ����ص���ʵ��������Ϸ�÷ֽ����֣���\n",
    "����һ����֮ʯ�����������(qidao / qd)���������������Լ�����֮�ء�\n",
    "����һ���ٻ�֮�У����������(zhaohuan / zh)�ٻ��������������Լ�����֮�ء�\n",
    "����һ�淢��֮�죬���������(fadai / fd)��ͬһ���ط����˷���һ�����\n",
    "����һ������֮�죬���������(quzhu / qz)��ĳ�ز��������֮������Żþ���Ϣ����ͣ����\n",
    "����һ��Ѱ��ˮ�������������(xunren / xr)Ѱ������һ������ʿ�������η���\n",
    "����һ�ſ�̽ˮ�������������(kuitan / kt)��̽����һ������ʿ�������������\n",
    "����һ����λ֮�ǣ����������(dingwei here / dw here)�ȶ�λ���ٿ��ٷ��ظõص�(dw back)��\n",
});

string *units=({
    "��",
    "��",
    "��",
    "��",
    "��",
    "��",
    "��",
    "��",
    "��",
    "��",
    "��",
});

int *times=({
    10+random(6),
    3+random(3),
    3,
    1,
    2+random(2),
    3+random(3),
    2+random(2),
    1,
    9,
    9,
    3,
});


// �����Ż��������ܷ�ʹ�õ��ߵ��ж��ڴ˽��С�
int can_use( string id, object me )
{
    if( !me || !id || query("id") != id ||
        !me->query_temp("huanjing") || me->query_temp("huanjing") != "start" ||
        !me->query_temp("hj_hp") || me->query_temp("hj_hp") < 1 ||
        query("use_times") <= 0 || !environment(me) ||
        !environment(me)->query("room_mark") )

        return 0;

    return 1;
}

// �����Ż��������ж� busy .
int hj_busy_now( object me )
{
    if( !me || me->is_busy() || me->query_temp("hj_need_waiting") ) return 1;
    return 0;
}

void setme( int iii )
{
    if( iii == 99 ) iii = random( sizeof(names) );
    set( "iii" , iii );

    set_name(names[ iii ],({ ids[ iii ] , ids2[ iii ] }));
    set_weight(100);
    if (clonep())
        set_default_object(__FILE__);

    set("long", longs[ iii ]);
    set("unit", units[ iii ]);
    set("value", 1);  // ��������º󲻻���ʧ��

    set("use_times",times[ iii ] );
    set("hj_game/obj","tools");
    set("msg","���ƺ������۾�һ�������ϲ�֪��ô�ľͶ���һ�����¡�\n");
}


void create()
{
    setme( 99 );
    setup();
}

void init()
{
    switch( query("iii") )
    {
        case 0: add_action("do_dingxiang", ({ "dingxiang", "dx" }) ); break;
        case 1: add_action("do_feixiang", ({ "feixiang", "fx" }) ); break;
        case 2: add_action("do_tuoli", ({ "tuoli", "tl" }) ); break;
        case 3: add_action("do_huigui", ({ "huigui", "hg" }) ); break;
        case 4: add_action("do_qidao", ({ "qidao", "qd" }) ); break;
        case 5: add_action("do_zhaohuan", ({ "zhaohuan", "zh" }) ); break;
        case 6: add_action("do_fadai", ({ "fadai", "fd" }) ); break;
        case 7: add_action("do_quzhu", ({ "quzhu", "qz" }) ); break;
        case 8: add_action("do_xunren", ({ "xunren", "xr" }) ); break;
        case 9: add_action("do_kuitan", ({ "kuitan", "kt" }) ); break;
        case 10: add_action("do_dingwei", ({ "dingwei", "dw" }) ); break;
    }

    if(query("qzzq_host_is"))
    {
        remove_call_out("get_out_here");
        call_out("get_out_here",1);
    }
}

void delete_me()
{
    if( query("real_name") )
    {
        message_vision(this_object()->query("real_name")+"�����Ѿ������ء���һ����ʧ�����ˡ�\n",this_object());
        environment()->delete("qzzq_now");
    }
    else
        message_vision(this_object()->query("name")+"�����Ѿ������ء���һ����ʧ�����ˡ�\n",this_object());
    destruct(this_object());
}

int do_dingxiang()
{
    object me = this_player(), ob = this_object(), rooms;
    int temp_mark;

    // ���Ż����жϾ�
    if( !can_use( "dx shuijing" , me ) )
        return 0;
    // �����߲��� busy ���ơ�
    //if( hj_busy_now( me ) ) return notify_fail("�㻹�б������æ���أ�\n");
    rooms = (environment(me));
    if(rooms && temp_mark = rooms->query("room_mark"))
    {
        message_vision(CYN"$N"NOR+CYN"����"NOR"$n"NOR+CYN"����ע���š�\n"NOR, me, ob );
        add("use_times",-1);
        // ���ٵļ��ʽ����ˡ�
        if( !random(5) )
        {
            temp_mark+= random(2) - random(2);
            if( temp_mark < 1 || temp_mark > HJ_ROOM_AMOUNT )
                temp_mark = 1+random( HJ_ROOM_AMOUNT );
        }
        write(query("name")+"����Լ������һ����ǣ��ƺ��� " + chinese_number(temp_mark) + " �� \n");
    }
    else
        return notify_fail("�˵ز��ǻþ������ڡ�\n");
    if( query("use_times") <=0 )
    {
        remove_call_out("delete_me");
        call_out("delete_me",1);
    }
    return 1;
}

int do_feixiang(string arg)
{
    object me = this_player(), ob = this_object(), rooms;
    int temp_mark;
    string goto_rooms;

    // ���Ż����жϾ�
    if( !can_use( "fx zhishi" , me ) )
        return 0;
    if ( !arg || !sscanf(arg, "%d",temp_mark) ) 
        return notify_fail("�����������Ϊ 1 - "+HJ_ROOM_AMOUNT+" ����������Ҫȥ�ĵط��ı�ǰɡ���\n");
    if( temp_mark < 1 || temp_mark > HJ_ROOM_AMOUNT)
        return notify_fail("�����������Ϊ 1 - "+HJ_ROOM_AMOUNT+" ����������Ҫȥ�ĵط��ı�ǰɡ���\n");
    if( hj_busy_now( me ) )
        return notify_fail("�㻹�б������æ���أ�\n");
    message_vision(CYN"$N"NOR+CYN"���ְ�$n"NOR+CYN"�������ģ����������ָ��һ������\n"NOR,me, ob);
    add("use_times",-1);
    // �ɴ�ļ��ʽ����ˡ�
    if( !random(5) )
    {
        temp_mark+= random(2) - random(2);
        if( temp_mark < 1 || temp_mark > HJ_ROOM_AMOUNT)
            temp_mark = 1+random(HJ_ROOM_AMOUNT);
    }
    goto_rooms = HJ_DIR +"hj_room"+ temp_mark;
    rooms = find_object(goto_rooms);
    if(!rooms)
        rooms = load_object(goto_rooms);
    message_vision(HIC"$N"HIC"�ڿն�����Զ����ȥ�ˡ�\n"NOR,me);
    me->move(rooms);
    message_vision(HIC"ֻ��$N"HIC"�ӿ���ƮȻ���£����ȵ����ڵ��ϡ�\n"NOR,me);
    if( query("use_times") <=0 )
    {
        remove_call_out("delete_me");
        call_out("delete_me",1);
    }
    return 1;
}

int do_tuoli()
{
    object me = this_player(), ob = this_object(), rooms;
    string random_rooms;

    // ���Ż����жϾ�
    if( !can_use( "tl shuijing" , me ) )
        return 0;
    message_vision(CYN"$N"NOR+CYN"��$n"NOR+CYN"����ץ��������߾ٹ�ͷ�������е���������˵أ���\n"NOR,me, ob);
    add("use_times",-1);
    random_rooms = HJ_DIR +"hj_room"+ (1+random(HJ_ROOM_AMOUNT));
    rooms = find_object(random_rooms);
    if(!rooms)
        rooms = load_object(random_rooms);
    message_vision(HIR"$N"HIR"����һ�Σ��漴��ʧ�����ˡ�\n"NOR,me);
    me->move(rooms);
    message_vision(HIR"$N"HIR"ͻȻ���������һ������δ�������ӡ�\n"NOR,me);
    if(query("use_times") <=0 )
    {
        remove_call_out("delete_me");
        call_out("delete_me",1);
    }
    return 1;
}

int do_huigui()
{
    object me = this_player(), ob = this_object(), rooms,qxd;

    // ���Ż����жϾ�
    if( !can_use( "hg zhijing" , me ) )
        return 0;
    if( hj_busy_now( me ) )
        return notify_fail("�㻹�б������æ���أ�\n");
    qxd = present( "qixing deng",me);
    if(!qxd || qxd->query("my_master") != me )
        return notify_fail("������û�����ǵƣ����������㲻���������ˣ�����\n��ʹ�� quit ָ��ǿ���˳���Ϸ��\n");
    if( !qxd ->query("can_quit_hj") )
        return notify_fail("��Ÿս�����Ϸû��ã���Ҫ�뿪��\n");
    if( qxd ->query("wait_over") == "yes" )
        return notify_fail("�����Ϸʱ�伴������������ʹ��"+query("name")+"�˰ɡ�\n");
    message_vision(CYN"$N"NOR+CYN"����"NOR"$n"NOR+CYN"�߾ٹ���������е�������ʵӳ�֣���\n"NOR,me, ob);
    set("use_times",0);
    qxd->set("use_huigui","yes");
    message_vision(WHT"ֻ��һ�����֪�Ӻδ�Ʈ����������Ũ����\n"NOR,me);
    remove_call_out("delete_me");
    call_out("delete_me",1);
    return 1;
}

int do_qidao()
{
    object ob = this_object(),me = this_player(),obj;
    string msg,*temp_list;

    if( !can_use( "qd zhishi", me ) )
        return 0;
    if( hj_busy_now( me ) )
        return notify_fail("�㻹�б������æ���أ�\n");
    message_vision(CYN"$N"NOR+CYN"˫������"NOR"$n"NOR+CYN"�����Ŀڣ���Ŀ��˵��ʲô��\n"NOR,me, ob);
    add("use_times",-1);
    if( !random(30) )  // ��ҽ��и���Ļ���õ������Լ��ı�����ɲ���
    {
        if( !me->query_temp("hj_game_find") ) return 1;
        temp_list=({"wait","wait"});
        switch( me->query_temp("hj_game_find") )
        {
            case "feng":
                temp_list=obj_list_feng; break;
            case "yu":
                temp_list=obj_list_yu; break;
            case "lei":
                temp_list=obj_list_lei; break;
            case "dian":
                temp_list=obj_list_dian; break;
        }
        if( temp_list[0] == "wait")
            return 1;
        obj=new( temp_list[0] );
        obj->set("host_id",me->query("id"));
        obj->setme( 1+random(2) );
        obj->move(environment(me));
        if(obj->query("msg")) msg=obj->query("msg");
        else msg="��ȻһС�������ӹ����������ƺ�����һЩʲô��\n";
        tell_room(environment(me),msg);
    }
    else
    {
        obj=new( obj_list_obj[random(sizeof(obj_list_obj))] );
        obj->move(environment(me));
        if(obj->query("msg")) msg=obj->query("msg");
        else msg="��ȻһС�������ӹ����������ƺ�����һЩʲô��\n";
        tell_room(environment(me),msg);
    }
    // busy �� 3�뽵Ϊ 1�롣
    me->start_busy(1);
    if( query("use_times") <=0 )
    {
        remove_call_out("delete_me");
        call_out("delete_me",1);
    }
    return 1;
}

int do_zhaohuan()
{
    object ob = this_object(),me = this_player(),obj;
    string msg,*temp_list;

    if( !can_use( "zh zhihe", me ) )
        return 0;
    if( hj_busy_now( me ) )
        return notify_fail("�㻹�б������æ���أ�\n");
    message_vision(CYN"$N"NOR+CYN"��������"NOR"$n"NOR+CYN"������ǰ���͵غ���һ�������������֣���\n"NOR,me, ob);
    add("use_times", -1);
    //ob->set("use_times",0);  // ���ﲻ֪Ϊ����BUG��Ϊ�˽����������һ�䡣
    // ����BUG
    if( !random(30) )  // ��ҽ��и���Ļ���õ������Լ��ı�����ɲ��֡�������NPCЯ�����
    {
        if( !me->query_temp("hj_game_find") ) return 1;
        temp_list=({"wait","wait"});
        switch( me->query_temp("hj_game_find") )
        {
            case "feng":
                temp_list=obj_list_feng; break;
            case "yu":
                temp_list=obj_list_yu;break;
            case "lei":
                temp_list=obj_list_lei;    break;
            case "dian":
                temp_list=obj_list_dian;break;
        }
        if( temp_list[0] == "wait")
            return 1;
        obj=new( temp_list[1] );
        obj->set("host_id",me->query("id"));
        obj->move(environment(me));
        if(obj->query("msg"))
            msg=obj->query("msg");
        else
            msg="��ȻһС�������ӹ����������ƺ�����һЩʲô��\n";
        tell_room(environment(me),msg);
    }
    else
    {
        obj=new( obj_list_npc[random(sizeof(obj_list_npc))] );
        obj->move(environment(me));
        if(obj->query("msg"))
            msg=obj->query("msg");
        else
            msg="��ȻһС�������ӹ����������ƺ�����һЩʲô��\n";
        tell_room(environment(me),msg);
    }
    if( query("use_times") <=0 )
    {
        remove_call_out("delete_me");
        call_out("delete_me",1);
    }
    return 1;
}

void fadai( object target, int time )
{
    object srl;
    // ���֮�����⼼������֮��(1)����Ч�ֿ�����֮��
    if( target->query_temp("hj_special/sh") )
    {
        message_vision( HIB"ֻ����$N"HIB"���ܺ�������һ������֮�������ǰ�$N"HIB"����������һ�㡣\n"
            "$N"HIB"����һЦ���������ȣ����ǶԷ���֮��������塣\n"NOR, target);
    }
    else if( (srl=present( "shenren ling", target )) )
    {
        message_vision( CYN"$N"NOR+CYN"���ϵ�"+srl->query("name")+NOR+CYN"ͻȻ����һ���â��"
            +"���ǰ�$N"NOR+CYN"����������һ�㡣\n"NOR, target );
    }
    // ��ʱ�뿪��Ϸ����֤�䰲ȫ
    else if( present( "hj temp leave obj", target ) )
    {
        message_vision( CYN"$N"NOR+CYN"���κ������֣����Ʋ���ʵ��һ�㣬����֮��ȴ�Ǻ����ô���\n"NOR, target );
    }
    else
    {
        message_vision(HIY"ֻ��$N"HIY"����˫Ŀ��ֱ����Ȼ���Ǹ����Ӱ�ģ����\n"NOR,target);
        target->start_busy( target->query_busy() + time );
    }
}
int do_fadai(string arg)
{
    object *inv_here,target,me=this_player(),ob=this_object(), srl;
    int time,human_amount,i;

    if( !can_use( "fd zhiqi", me ) )
        return 0;
    // ������æʱ
    //if( hj_busy_now( me ) )
        //return notify_fail("�㻹�б������æ���أ�\n");
    if(!arg)
        return notify_fail("��Ҫ��˭��������ʽ��\n"
            "��ĳ�˷��� <fadai "+me->query("id")+"> \n"
            "������ط�����������Ϣ���˷��� <fadai all> (��Ҫ�����������Ϣ)\n");
    if(!me->query_temp("hj_game_mepower"))
        time=3;
    else
        time= 5 + random(me->query_temp("hj_game_mepower"));
    if(time > 60)
        time = 60;
    if(time < 10)
        time = 10;
    if(arg != "all")
    {
        target = present(arg , environment( me ) );
        if(!target)
            return notify_fail("����û������ˡ�\n");
        if(!target->is_character())
            return notify_fail("�ⲻ�ǻ��\n");
        if(!target->query_temp("hj_hp") || target->query_temp("hj_hp") <1 )
            return notify_fail(target->query("name")+"û�лþ������Ϣ���޷�������й�����\n");
        if(!living(target))
            return notify_fail("�����Ϸ����������ѵĶ��ֲ��ܹ�����\n");
        if( target == me )
            return notify_fail("���Լ�������û��Ҫ�ɡ���\n");
        message_vision(HIY"$N"HIY"����"NOR"$n"HIY"�����е��������ӳ��֣���\n"NOR,me, ob);
        fadai( target, time );
    }
    else
    {
        if(me->query_temp("hj_hp") < 60 )
            return notify_fail("�����Ϣ������ʹ���������������\n");
        inv_here = all_inventory(environment(me));
        if(!inv_here || sizeof(inv_here) < 2)
            return notify_fail("���û����ˣ�����Ǹ�����������ʡ�ŵ��ðɡ�\n");
        for(i=0;i<sizeof(inv_here);i++)
        {
            if( inv_here[i] ->query_temp("hj_hp") &&
                inv_here[i]->query_temp("hj_hp") > 0 &&
                inv_here[i] != me )
            human_amount++;
        }
        if( human_amount < 1 )
            return notify_fail("���û����ˣ�����Ǹ�����������ʡ�ŵ��ðɡ�\n");
        message_vision(HIY"$N"HIY"����"NOR"$n"HIY"��˻���߰�����к�������һ�Ѵ��ӣ������֣���\n"NOR,me, ob);
        for(i=0;i<sizeof(inv_here);i++)
        {
            if( inv_here[i] ->query_temp("hj_hp") &&
                inv_here[i]->query_temp("hj_hp") > 0 &&
                inv_here[i] != me
            )
                fadai( inv_here[i], time );
        }
        me->add_temp("hj_hp",- (25 + random(26) ) );
        tell_object(me,"����֮�󣬾������������ġ�\n");
    }
    add("use_times",-1);
    if( query("use_times") <=0 )
    {
        remove_call_out("delete_me");
        call_out("delete_me",1);
    }
    return 1;
}

int do_quzhu()
{
    object env, me=this_player(), ob=this_object();
    if( !can_use( "qz zhiqi", me ) )
    {
        write("ʲô��\n");
        return 1;
    }
    // ����æʱ���ơ�
    //if( hj_busy_now( me ) ) return notify_fail("�㻹�б������æ���أ�\n");
    env = environment(me);
    if(env->query("room_mark") == 1)
        return notify_fail("�㲻��������ط���������֮�졣\n");
    if( env->query("qzzq_now") )
    {
        write("�����Ѿ����˲�������֮���ˡ�\n");
        return 1;
    }
    set("qzzq_host_is",me->query("id") );
    add("use_times",-1);
    set("use_times",0); // ��bug�ޣ�������䲻�У�����.
    set("real_name","���ڵ��ϵ�����֮��");
    set("no_refresh", 1 );
    if( environment(this_object()) != me )
        message_vision(CYN"$N"NOR+CYN"��"NOR"$n"NOR+CYN"����������ʹ���ز嵽�˵��ϣ�\n"NOR,me, ob);
    else
        message_vision(CYN"$N"NOR+CYN"������ȡ��"NOR"$n"NOR+CYN"��ʹ���ز嵽�˵��ϣ�\n"NOR,me, ob);
    message_vision(HIB"��ʱ����������������Ҳ����������\n"NOR,me);
    move( env );
    set_weight(6300000);
    env->set("qzzq_now", 1);
    ob->get_out_here();
    ob->set_name(HIM"��������������һ�� ����֮�� ���ڵ��ϡ�������������"NOR,({"��"}));
    remove_call_out("delete_me");
    call_out("delete_me",180+random(300));
    // ʱ���ӳ�����ԭ���� 2-3 �����ӳ��� 3-5 ���ӡ�
    return 1;
}

void get_out_here()
{
    object *inv_here,srl,random_rooms;
    string temp;
    int i;
    inv_here = all_inventory(environment(this_object()));
    for(i=0;i<sizeof(inv_here);i++)
    {
        if( inv_here[i]->query("id") == query("qzzq_host_is") )
            continue;
        if( !inv_here[i]->query_temp("hj_hp") )
            continue;
        srl = present("shenren ling" , inv_here[i] );
        if(srl)
        {
            message_vision( HIC+query("real_name")+""HIC"����һ��ҫ�۹�â������\n"
                +"ȴ��$N"HIC"���ϵ�"+srl->query("name")+HIC
                +"Ҳɢ��һ���â�����Ǳ���Ȧ���$N"HIC"Χ��������\n"NOR,
                inv_here[i] );
            continue;
        }
        // �����ʱ�뿪���������ɫ�İ�ȫ��
        if( present( "hj temp leave obj", inv_here[i] ) )
        {
            continue;
        }
        message_vision(HIC+query("real_name")+""HIC"����һ��ҫ�۹�â������ֻ��$N"
            +HIC"���ɼ���������˳�ȥ��\n"NOR,inv_here[i]);
        if(inv_here[i]->query_temp("hj_flying") )
        {
            inv_here[i]->delete_temp("hj_flying");
            temp = HJ_DIR  +"hj_room"+ 1;
        }
        else
        {
            inv_here[i]->set_temp( "hj_flying", 1 );
            temp= HJ_DIR  + "hj_room" + ( 1+random(HJ_ROOM_AMOUNT) );
        }
        random_rooms=find_object( temp );
        if(!random_rooms)
            random_rooms=load_object( temp );
        inv_here[i]->move(random_rooms);
        message_vision("$N�Ӱ���е�����������֪������ô���¡�\n",inv_here[i]);
    }
}

int do_xunren(string arg)
{
    object ob=this_object(),me=this_player(),target,rooms;
    int temp_mark;

    if( !can_use( "xr shuijing", me ) )
        return 0;
    // ����æʱ���ơ�
    //    if( hj_busy_now( me ) ) return notify_fail("�㻹�б������æ���أ�\n");
    if(!arg)
        return notify_fail("��ҪѰ��ʲô�ˣ�\n");
    if( arg == me->query("id") )
        return notify_fail("�þ�����Ȼ��Щ��ħ��֣�����"+me->query("name")+"����һ�����ѣ�û�и�����ˡ�\n");
    target = find_player(arg);
    if(!target)
        return notify_fail("���ڲ�û�����������ߣ�ĪҪ˵�������ˡ�\n");
    rooms = (environment(target));
    if( !rooms || !rooms->query("room_mark") )
        return notify_fail("�þ��������ﲢû�������ҡ�\n");
    temp_mark = rooms->query("room_mark");
    message_vision(CYN"$N"NOR+CYN"����"NOR"$n"NOR+CYN"����ע���ţ���Ҫ���п���ʲô����\n"NOR,me, ob);
    add("use_times",-1);
    // Ѱ��ļ��ʽ����ˡ�
    if( !random(5) )
    {
        temp_mark += random(2) - random(2);
        if( temp_mark < 1 || temp_mark > HJ_ROOM_AMOUNT )
            temp_mark = 1+random( HJ_ROOM_AMOUNT );
    }
    write(query("name")+"����Լ�����ų���ǣ��ƺ��� "+chinese_number(temp_mark)+" ��\n");
    if( query("use_times") <=0 )
    {
        remove_call_out("delete_me");
        call_out("delete_me",1);
    }
    return 1;
}

int do_kuitan(string arg)
{
    object target,*inv,me=this_player();
    int i;
    string target_name;

    if( !can_use( "kt shuijing", me ) )
        return 0;
    // ����æʱ���ơ�
    //    if( hj_busy_now( me ) ) return notify_fail("�㻹�б������æ���أ�\n");
    if(!arg)
        return notify_fail("��Ҫ��̽˭�����ң�\n");
    target = present(arg , environment( me ) );
    if(!target)
        return notify_fail("����û������ˡ�\n");
    if(!target->is_character())
        return notify_fail("�ⲻ�ǻ��\n");
    if(target->query("hj_game/npc"))
        return notify_fail("�ⲻ������һ���������ʿ��\n");
    if(!target->query_temp("hj_hp") || target->query_temp("hj_hp") <1 ||
       target->query_temp("huanjing") != "start" )
        return notify_fail(target->query("name")+"��û��˿���þ������Ϣ�����˰ɡ�\n");
    if(!living(target))
        return notify_fail("�����Ϸ����������ѵĶ��ֲ��ܽ��в�����\n");
    inv = all_inventory(target);
    if(target == me)
        target_name="��";
    else
        target_name = target->query("name");
    tell_object(me,"�����ĵ�����ˮ������ϸ�ؿ��š���\n");
    if( !inv || sizeof(inv)<1 )
        return notify_fail(target_name+"����û�����κζ�����\n");
    for(i=0;i<sizeof(inv);i++)
    {
        if( inv[i]->query("hj_game/obj") && random(3) )
        {
            tell_object(me,sprintf("%s�����ƺ�����һ%s%s��\n",
                target_name,inv[i]->query("unit"),inv[i]->query("name")));
        }
    }
    // ʹ��æʱȡ�������ٸ��Է���ʾ��
    //     if( target != me) tell_object(target,HIB"��ֻ�����ƺ���Щ�������۹���̽�����Լ�һ�㡭��\n"NOR);
    //    tell_object(me,"�㶢�ſ����ˣ���Ȼ������Щ���Ƶġ�\n");
    //    me->start_busy(5+random(6));
    add("use_times",-1);
    if(query("use_times") <=0 )
    {
        remove_call_out("delete_me");
        call_out("delete_me",1);
    }
    return 1;
}

int do_dingwei( string arg )
{
    object me = this_player(), ob = this_object(), the_room;
    string room_name;

    if( !can_use( "dw zhiyi", me ) )
        return 0;
    if( hj_busy_now(me) )
        return notify_fail("�㻹æ���ء�\n");
    if( !arg || (arg != "here" && arg != "back") )
        return notify_fail("��Ҫ�����ﶨλ(dingwei here)����Ҫ����(dingwei back)֮ǰ��λ�ĵص㣿\n");
    if( arg == "here" )
    {
        message_vision(CYN"$N"NOR+CYN"�ó�$n"NOR+CYN"������һ����ǡ�\n"NOR, me, ob );
        set( "dingwei_" + me->query("id"), environment(me)->query("room_mark") );
        me->start_busy(1);
        return 1;
    }
    // ������Ƿ��ظõص�
    if( !query( "dingwei_" + me->query("id") ) )
        return notify_fail("��"+query("name")+"û�������Ķ�λ��ǣ�����ص�����ȥ��\n");
    room_name = HJ_DIR + "hj_room" + query("dingwei_" + me->query("id") );
    the_room = find_object( room_name );
    if( !the_room )
        the_room = load_object( room_name );
    if( !the_room )
        return notify_fail("����ǰ���µı�ǲ�֪��ô����ʧ�ˣ��ز�ȥ��\n");
    message_vision(CYN"$N"NOR+CYN"����$n"NOR+CYN"�������ȵ�����ȥ����\n"NOR, me, ob);
    message_vision(HIW"$N"HIW"��������һ�Σ���ʧ�����ˡ�\n"NOR, me);
    me->move( the_room );
    message_vision(HIW"$N"HIW"ͻȻ���������\n"NOR, me );
    me->start_busy(1);
    add( "use_times", -1 );
    if(query("use_times") <=0 )
    {
        remove_call_out("delete_me");
        call_out("delete_me",1);
    }
    return 1;
}

