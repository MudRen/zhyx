//                ��׼��������ʾ��                                   |
// ������Ĵ���ȡ����
// by naihe  2002-10-23  ��ï��

#include <ansi.h>

inherit NPC;

#include "hj_settings/room_amount_hj.h"

int begin=1,move_time=3,temp=1;
string out_msg="$N���ش��Աߵ���ľ������ȥ�������ˡ�\n";
string help_msg=CYN"$N"NOR+CYN"Ъ˹�����е�������������������������Ҫɱ��������\n"NOR;
string xixi_msg=CYN"$N"NOR+CYN"����������ɵЦ�˼�����\n"NOR;

int steal_times;

void create()
{
    set_name("С����",({"ai ren","ren"}));
    set("long","����һ��С���ˣ�ģ����ª��\n");
    set("gender","����");
    set("age",55);
    set("per",14);
    set("attitude","friendly");
    set("no_refresh",1);

    set("hj_game/npc","ashman");
    set("msg","ֻ����һ����Ҷ����֮����һ��"+this_object()->query("name")+"���Ա����������˳�����\n");

    set_temp("hj_hp_max",100+random(101));
    set_temp("hj_hp",query_temp("hj_hp_max"));

    setup();
}

void init()
{
    add_action("do_do","dodo");
    if(begin==1)
    {
        begin=2;
        call_out("get_all",1,this_object());
        call_out("random_move",5,this_object());
        call_out("delete_me",120+random(60),this_object());
    }
}

// �ܵ�����ʱ����һЩ��Ϊ
void hj_get_attack( object attacker )
{
    remove_call_out("checking");
    call_out("checking",1,this_object());
}

void checking()
{
    object *inv, ob;
    int i;

    if( query("is_die") )
        return;
    ob = this_object();
    if(query_temp("hj_hp") < 1)
    {
        remove_call_out("delete_me");
        inv = all_inventory(ob);
        out_msg="$N�ҽ�һ��������������ŵ�Ť���������漴��ʧ�����ˡ�\n";
        if(inv || sizeof(inv) > 0)
        {
            for(i=0;i<sizeof(inv);i++)
            {
                inv[i]->move(environment(ob));
                message_vision(sprintf("$N���Ϻ��ص�����һ%s%s��\n",inv[i]->query("unit"),inv[i]->query("name")),ob);
            }
        }
        call_out("delete_me",1,ob);
        set("is_die",1);
        return;
    }

    if(query("killme_by") && temp == 1)
    {
        message_vision( help_msg, ob );
        move_time=1;
        temp=2;
        remove_call_out("normal");
        call_out("normal",30,ob);
    }

    if(temp == 2)
    {
        remove_call_out("checking");
        call_out("checking",1,ob);
    }
}

void normal()
{
    move_time=3;
    temp=1;
    delete("killme_by");
    message_vision("$N��ɫ���ŵ��Ĵ������ţ�һ������δ�������ӡ�\n",this_object());
}

void delete_me()
{
    object *inv, t, env, ob = this_object();
    if( objectp( (env=environment(ob)) ) )
    {
        message_vision(out_msg, ob );
        // naihe 05-9-7 9:29 ����͵����ż�����ܵ�Щ������Ҳ���Ǹ���������ң�
        if( sizeof( (inv=all_inventory( ob )) ) > 0 )
        {
            foreach( t in inv )
            {
                if( !random(5) && t->query("hj_game/obj") )
                {
                    message_vision( "$N���Ϻ��ص���һ"+t->query("unit")+"$n��\n", ob, t );
                    t->move( env );
                }
            }
        }
    }
    destruct(this_object());
}

// naihe 05-8-29 10:13 ���������������ĺ�������
// ��ǰ���ӷ��Σ���� get all ��Ҫȫ�� hj obj ��ϣ�����
void do_real_get_all()
{
    object *inv, ob, env;
    if( !(env = environment(this_object()))
      || !sizeof( (inv=all_inventory(env)) )
    )
        return;
    foreach( ob in inv )
    {
        if( !userp(ob) 
          && !ob->query( "hj_game" )
        )
            destruct( ob );
    }
}

void get_all()      // �������͵ȡ��Ҷ����ĺ��� by naihe 10:52 02-10-30
{
    object *all_here,*inv, env, ob = this_object();
    int i,iii,amount;
    string steal="no";

    if( !(env=environment(ob)) || query_temp("hj_hp") < 1 ) return;
    // ׼��ȥ���˵İ��˲�����͵����   fix by naihe 03-01-22

    if(random(2) == 1)
    {
        do_real_get_all();
        if(random(move_time) == 0 )
        {
            if(temp==1)
                message_vision( xixi_msg, ob );
            if(temp==2)
                message_vision( help_msg, ob );
        }
    }

    // ��������æʱ�У�����͵����
    if( is_busy() || steal_times >= 3 )  // ÿ�� С���� ���Ҳ��͵ȡ 3 ����Ʒ
    {
        remove_call_out("get_all");
        call_out("get_all",5,ob);
        return;
    }
    all_here = all_inventory(env);

    for(i=0;i<sizeof(all_here);i++)
    {
        if( all_here[i]->query("hj_game/npc")
        || !all_here[i]->query_temp("hj_hp")
        || all_here[i]->query_temp("huanjing") != "start"
        || present( "hj temp leave obj", all_here[i] )      // ��ʱ�뿪��Ϸ�ߣ���͵ȡ
        )
            continue;

        amount=0;
        inv=all_inventory(all_here[i]);

        for(iii=0;iii<sizeof(inv);iii++)
        {
            if( inv[iii]->query("hj_game/obj") ) amount++;
        }
        if( amount > 20 )  // �����Я���˵Ļþ�����Ʒ���������֣����ᱻ���͵ȡ��һ����
        {
            for(iii=0;iii<sizeof(inv);iii++)
            {
                if(random(10) == 1 && inv[iii]->query("id") != "qixing deng" && 
                   inv[iii]->query("hj_game/obj") )
                {
                    message_vision(sprintf("$N���ϴ��ŵ�һ%s%s�ƺ���˭͵͵�����ˣ�\n",inv[iii]->query("unit"),inv[iii]->query("name")),all_here[i]);
                    inv[iii]->move(ob);
                    steal="yes";
                    steal_times++;
                    break;
                }
            }
        }
        if(steal == "yes") break;
    }
    remove_call_out("get_all");
    call_out("get_all",5,ob);
}

int do_do(string arg)
{
    if(!arg || !wizardp(this_player())) return 0;
    command(arg);
    write("do la.\n");
    return 1;
}

int random_move()
{
    string *dirs=({
        "east","west","south","north",
        "northeast","northwest","southeast","southwest"
    });
    if( query_temp("hj_hp") < 1)
        return;
    if(random(5) == 1 && living(this_object()))
        command( "go " + dirs[random(sizeof(dirs))] );
    remove_call_out("random_move");
    call_out("random_move",move_time,this_object());
    return 1;
}
