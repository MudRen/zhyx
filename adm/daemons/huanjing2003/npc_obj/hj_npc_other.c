//                ��׼��������ʾ��                                   |
// �þ�������  ������
// ���� ���ڼ��ܡ��ָ�������Ѱ����н�����
// by naihe  2002-10-29  ��ï��

#include <ansi.h>

inherit NPC;

#include "hj_settings/room_amount_hj.h"

string *colors=({
    ""HIR"",
    ""HIY"",
    ""HIG"",
    ""HIC"",
    ""HIW"",
    ""HIM"",
});
// ��Ҫ HIB ��ɫ�ľ��� ����


int *move_time = ({ 5, 10, 2, 3 });
int *job_times = ({ 5, 10, 10, 3 });


int ask_find();

string me_find_name = "�Ҷ���";


void setme( int iii )
{
    string cl = colors[ random( sizeof(colors) ) ];

    if( iii == 99 ) iii = random(4);
    set("iii", iii ); // �˴� iii Ϊ���ͱ�ǡ�

    set_name( cl+"С����"NOR, ({"jing ling", "jl", "ling" }) );
    set("msg",cl+"һ�����㴫����ֻ���Ա������Ƶطɹ���һ��С���顣\n"NOR);

    set("job_times", job_times[ iii ] );

    set("long","����һ��������ɽҰ��С���飬ֻ�������˵����ƴ�С��ģ�����ǿɰ���\n");
    set("hj_game/npc","other");

    set("gender","Ů��");
    set("age",12+random(12));
    set("per",20+random(5));

    set("inquiry",([
        me_find_name : (: ask_find :),
        ]));

    set("no_refresh",1);

    remove_call_out("delete_me");
    remove_call_out("random_move");
    remove_call_out("random_teach");
    remove_call_out("random_heal");
    remove_call_out("random_drop");
    remove_call_out("random_find");

    call_out("do_all_start", 3);
}

void create()
{
    setme( 99 );
    setup();
}

void do_all_start()
{
    if( !environment(this_object()) ) return;

    call_out("delete_me", 240 + random( 60 ) );
    call_out("random_move", 1);

    switch( query("iii") )
    {
        case 0: call_out("random_teach",1); break;
        case 1: call_out("random_heal",1); break;
        case 2: call_out("random_drop",1); break;
        case 3: call_out("random_find",1); break;
    }
}


void delete_me()
{
    message_vision("$N�������������������ؾͲ�֪����δ�ȥ�ˡ�\n",this_object());
    destruct(this_object());
}

int random_move()
{
    string *dirs=({
"east","west","south","north","northeast","northwest","southeast","southwest"
        });

    if(random(3) == 1 && living(this_object()))
        command(dirs[random(sizeof(dirs))]);

    remove_call_out("random_move");
    call_out("random_move", move_time[ query("iii") ] );
    return 1;
}

void random_teach()
{
    object *inv,target,ob=this_object();
    int i;
    string *skills_ids,*skills_names;

    if( query("job_times") < 1 )
    {
        remove_call_out("delete_me");
        call_out("delete_me",10);
        return;
    }

    if(random(2) == 1)
    {
        inv = all_inventory(environment(ob));
        if(inv && sizeof(inv) > 0)
        {
            target = inv[random(sizeof(inv))];
            if(target->is_character() &&
                   target->query_temp("huanjing") == "start" &&
               living(target) && random(2) == 1)
            {

// ���濪ʼ������������� :)

    skills_ids=({"hfzj","hyzj","llzj","ydzj","gszj","fhzj","dhzj","heal"});
    skills_names=({"����֮��","����֮��","����֮��",
    "����֮��","��ʯ֮��","�ɻ�֮��","���֮��","�ָ�֮��"});
    i=random(sizeof(skills_ids));

    if(!target->query_temp("hj_game_skills/"+skills_ids[i]))
    {
        command("whisper "+target->query("id")+" ��������������á�"+skills_names[i]+"�������Űɣ�");
        command("whisper "+target->query("id")+" ����������������������������");
        command("smile "+target->query("id"));
        ob->add("job_times",-1);
        target->set_temp("hj_game_skills/"+skills_ids[i],skills_names[i]);
        target->set_temp("hj_game_damages/"+skills_ids[i],3+random(3));
        message_vision(CYN"$N"NOR+CYN"ֻ����ͻȻ֮������������������ˡ�"+skills_names[i]+"����\n"NOR,target);
    }
    else
    {
        command("whisper "+target->query("id")+" ����������μ�ǿ��"+skills_names[i]+"�����������Űɣ�");
        command("whisper "+target->query("id")+" ����������������������������");
        command("pat "+target->query("id"));
        ob->add("job_times",-1);
        if( target->query_temp("hj_game_damages/" + skills_ids[i] ) < 99 )
        {
        target->add_temp("hj_game_damages/"+skills_ids[i],2+random(2));
        message_vision(CYN"$N"NOR+CYN"��ϸ���ţ��ƺ������Լ���"+skills_names[i]+"������Ϊ�����������ˡ�\n"NOR,target);
        if(target->query_temp("hj_game_damages/"+skills_ids[i]) > 99)
            target->set_temp("hj_game_damages/"+skills_ids[i], 99);
        }
        else
        message_vision( CYN"$N"NOR+CYN"������Ц�����������ѵ�֪���й��ϣ����ط����ˡ���\n"NOR,target);
    }
            }
        }
    }

    if(random(3) == 1) message_vision(CYN"$N"NOR+CYN"�Ĵ��������������������غ�����ʲô�������\n"NOR,this_object());
    remove_call_out("random_teach");
    call_out("random_teach",10+random(11));
}


void random_heal()
{
    object *inv,target,ob=this_object();
    int hp,hp_max;

    if(query("job_times")<1)
    {
        remove_call_out("delete_me");
        call_out("delete_me",10);
        return;
    }

    inv = all_inventory(environment(ob));
    if(inv && sizeof(inv) > 0)
    {
        target = inv[random(sizeof(inv))];
        if(target->is_character() &&
               target->query_temp("huanjing") == "start" &&
           living(target) && target->query_temp("hj_hp") > 0 &&
           target->query_temp("hj_hp_max") > 0 )
        {

// ���濪ʼ�������һָ���Ϣ

    if(target->query_temp("hj_hp") < (target->query_temp("hj_hp_max") *8/10) )
    {
        hp=target->query_temp("hj_hp");
        hp_max=target->query_temp("hj_hp_max");

        command("idle2 "+target->query("id"));
        message_vision("$n"NOR+CYN"����$N"NOR+CYN"��������˾�ʲô��ֻ��$N"NOR+CYN"����ɫ��ʱ��Ϊ��ת��\n"NOR,target, ob );
        ob->add("job_times",-1);
        hp+=30+random(hp_max/10);
        if(hp>hp_max) hp = hp_max;
        target->set_temp("hj_hp",hp);
    }
        }
    }

    if( !random(3) )
        message_vision(CYN"$N"NOR+CYN"�Ĵ�����������������Ц��һ����\n"NOR, ob);
    remove_call_out("random_heal");
    call_out("random_heal",5+random(6));
}

void random_drop()
{
    object guo, ob = this_object();

    if(query("job_times")<1)
    {
        remove_call_out("delete_me");
        call_out("delete_me",10);
        return;
    }

    if(random(3) == 1)
    {
        guo = new(__DIR__"hj_obj_other");
        guo->setme(0);
        guo->move(environment(this_object()));
        message_vision(CYN"$N"NOR+CYN"���Ϻ��ص���һ��С���ӣ�\n"NOR, ob );
        this_object()->add("job_times",-1);
    }

    if(random(3) == 1) message_vision(CYN"$N"NOR+CYN"����س��������ɹ������ɹ��������Ϳ����ɻ������\n"NOR, ob );
    remove_call_out("random_drop");
    call_out("random_drop",10+random(11) );
}

void random_find()
{
    int i;
    string *find_names,*find_ids;
    object ob = this_object();

    if(query("job_times")<1)
    {
        remove_call_out("delete_me");
        call_out("delete_me",10);
        return;
    }

    if(!query("me_find_id") && random(5) == 1)
    {

find_names=({"����ˮ��","����֮ʯ","����ˮ��","�ع�֮��","��֮ʯ","�ٻ�֮��",
"����֮��","����֮��","Ѱ��ˮ��","��λ֮��",
"��ɫ��ʯ","��ɫ��ʯ","��ɫ��ʯ",
"����֮ʯ","����֮ʯ","����֮ʯ","����֮ʯ","��ʯ֮ʯ","�ɻ�֮ʯ","���֮ʯ","����֮ʯ",
"��֮ͭ��","����֮��","����֮��","ӯ��֮��","�ƽ�֮��",
"����֮��","Ѹ��֮��","���֮��","��ʤ֮��","���ˮ��",
"����ˮ��","����ˮ��","����ˮ��","��ʯˮ��","�ɻ�ˮ��","���ˮ��",
});

find_ids=({"dx shuijing","fx zhishi","tl shuijing","hg zhijing","qd zhishi","zh zhihe",
"fd zhiqi","qz zhiqi","xr shuijing","dw zhiyi",
"red baoshi","blue baoshi","green baoshi",
"hufeng shi","huanyu shi","luolei shi","yindian shi",
"gunshi shi","feihuo shi","duohun shi","fuhuo shi",
"qt jian","lq jian","by jian","yd jian","hj jian",
"nl jian","bj jian","dh jian","bs jian","kf sj",
"by sj","ll sj","yd sj","gs sj","fh sj","dh sj",
});

        i=random(sizeof(find_names));
        set("me_find_id",find_ids[i]);
        me_find_name = find_names[i];
        set("inquiry",([
            me_find_name : (: ask_find :),
            ]));
    }

    if(!query("me_find_id") && random(2) == 1)
message_vision(CYN"$N"NOR+CYN"����س���������ѰѰѰ���������٣���ôȴ������Ҫ�ҵĶ�������\n"NOR, ob );

    else if(query("me_find_id") && random(2) == 1)
message_vision(CYN"$N"NOR+CYN"����س���������ѰѰѰ���������٣���ôȴ������Ҫ�ҵ�"+me_find_name+"����\n"NOR, ob );

    remove_call_out("random_find");
    call_out("random_find",5+random(6));
}

int ask_find()
{
    object find,srl,me = this_player(), ob = this_object();

    if(!query("me_find_id") )
    {
        command("sing");
        return 1;
    }

    find=present(query("me_find_id"),me);
    if(!find)
    {
        command("say ����Ҫ����ѽ����������ܰ������ң��Ǹö��ѽ��");
        command("xixi");
        return 1;
    }
    if(!find->query("hj_game/obj"))
    {
        command("say ��ѽ������ŵ�����������������Ҫ���Ǹ����ѽ��");
        command("giggle");
        return 1;
    }

    message_vision(CYN"$N"NOR+CYN"�ó�һ"+find->query("unit")+find->query("name")+NOR+CYN"�ݸ�$n"NOR+CYN"��\n"NOR, me, ob );
    destruct(find);
    command("wa "+me->query("id"));
    command("touch");
    srl=new(__DIR__"shenren_ling");
    srl->waiting_delete( 120+random(60) );
    message_vision("$n"NOR+CYN"�ó�һ"+srl->query("unit")+srl->query("name")+NOR+CYN"�ݸ���$N"NOR+CYN"��\n"NOR, me, ob);
    srl->move(me);
    command("blush "+me->query("id"));
    delete("me_find_id");

    remove_call_out("random_find");
    call_out("random_find",10);
    return 1;
}
