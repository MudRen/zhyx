// for feng_npc.c yu_npc.c lei_npc.c dian_npc.c

string *songs3=({
    "�װ�������",
    "�������˵������Զ�ŵ�ʱ��",
    "���й��Ĺ��Ϲ��ȵĹ��£�",
    "�������Ÿ���������ı���",
    "Ҳ�������Ͷ�����������",
    "�������ڵĵط���",
    me_guodu,
    baowu_name+"��"+baowu_other1+"��"+baowu_other2,
    "�������������Ϊ֮���Ե�",
    "��֮���",
    "���װ�������",
    "�������Ѱ������",
    "��Ҳ���ܹ����������յ�",
    "���ع��ȵ�����֮�⡣",
});

int ask_all();
int ask_baowu();

int singing=0;

void sing_song();
int i=0;

string *songs;
object baowu;

void wait_singsong();

string *gem_names=({
    "��Ұ�屦��",
    "�����屦��",
    "�����屦��",
    "ɽ���屦��",
    "�����屦��",
});

string *gem_ids=({
    "manye baowu",
    "mengli baowu",
    "aiyao baowu",
    "shanguai baowu",
    "juren baowu",
});



#include "hj_settings/obj_list.h"
#include "hj_settings/room_amount_hj.h"



void create()
{
    set_name("����",({"chen min"}));
    set("long","��������Թ��ϵ�"+me_guodu+"������֪�����ǹ��������ɡ�\n");
    if(random(2) == 1) set("gender","����");
    else set("gender","Ů��");
    set("title",me_guodu);
    set("age",20+random(100));
    set("per",18+random(5));
    set("attitude","friendly");
    set("no_refresh",1); // ���ᱻ������¡�
    set("inquiry",([
        "all": (: ask_all :),
        ask_arg : (: ask_baowu :),
        "����" : (:  ask_baowu :),
        ]));
    set("hj_game/npc", me_mark[0]);
    set("host_id","no");
    set("msg", HIW"ֻ��һ����Ӱ��������������ƾ�ճ�����һ��İ�����ˡ�\n"NOR);

        set("chat_chance", 1);
        set("chat_msg", ({ (: wait_singsong :) }));

    setup();

    remove_call_out("checking");
    remove_call_out("delete_me");
    call_out("checking", 1);
    call_out("delete_me",2400+random(600) ); // ������Ϸ�Ѷȣ�40 - 50��������ʧ��
// �����ǵ��ڵ����� deng_time Ϊ 300 �Ļ���������Ҫ�ָ�Ϊ 1800+random(600) ��

}

// �����NPC��������Ҳ����ڻ����˳���Ϸ����NPC�����
void checking()
{
    object my_host;

    if( !environment( this_object() ) ) return;

    my_host=find_player(query("host_id"));
    if(!my_host || !my_host->query_temp("huanjing") ||
       my_host->query_temp("huanjing") !="start" ||
       !my_host->query_temp("hj_hp") || !my_host->query_temp("hj_hp_max") ||
       my_host->query_temp("hj_find_ok") == "yes")
    {
        remove_call_out("delete_me");
        call_out("delete_me",5);
    }

    else
    {
        remove_call_out("checking");
        call_out("checking",1);
    }
}

int ask_all()
{
    command("smile");
    command("say ����֪����ɽ֮�ߣ��纣֮�����������ô��");
    return 1;
}

void wait_singsong()
{
    if( singing == 0 )
    {
        remove_call_out("sing_song");
        i=0;
        singing=1;
        if(random(3) == 1) songs=songs1;
        else if(random(3) == 1) songs=songs2;
        else songs=songs3;
        message_vision(CYN"$N"NOR+CYN"΢΢һЦ�����������˸�����\n"NOR,this_object());
        call_out("sing_song",2);
    }
}

void sing_song()
{
    message_vision(CYN"      "+songs[i]+"\n"NOR,this_object());
    i++;

    if( i < sizeof(songs) )
    {
        remove_call_out("sing_song");
        call_out("sing_song",3);
    }
    else
    {
        remove_call_out("song_over");
        call_out("song_over",2);
    }
}

void song_over()
{
    message_vision(CYN"\n$N"NOR+CYN"���գ�����΢΢һЦ����������������¡�\n"NOR,this_object());
    singing=0;
}

void delete_me()
{
    object my_host;

    if( !environment( this_object() ) ) return;

    my_host=find_player(query("host_id"));
    if(my_host && my_host->query_temp("huanjing") =="start" &&
       my_host->query_temp("hj_find_ok") != "yes" )
        tell_object(my_host,HIR"�������ƺ��ӹ�һ˿������ȴ�ֲ�֪��Ϊʲô��\n"NOR);

    message_vision(HIW"$N"HIW"�ƺ�����ʧ���������һ�£�ҡ��ҡͷ��������ʧ�����ˡ�\n"NOR,this_object());
    remove_call_out("sing_song");
    destruct(this_object());
}

int ask_baowu()
{
    object me,tianma_zhishen,ob,obj1,obj2,gem_npc,my_gem,gem_rooms;
    int temp_i;
    string gem_name,gem_id;

    if( !environment(this_player())->query("room_mark") && !wizardp(this_player()))
        return 0;

    me=this_player();
    ob=this_object();

    if( !me->query_temp("huanjing") || me->query_temp("huanjing") != "start" ||
        !me->query_temp("hj_hp") || me->query_temp("hj_hp") < 1 )
        return 0;

    if( singing == 1) 
    {
        write(ob->query("name")+"���ڳ����أ������пջش���ѽ��\n");
        return 1;
    }

    if( ob->query("host_id") != me->query("id") )
    {
        message_vision(CYN"$N"NOR+CYN"΢΢Ц��һЦ��ȴ����˵����\n"NOR,ob);
        return 1;
    }

    obj1=present(me_mark[1],me);
    obj2=present(me_mark[2],me);


// ���Ҫ�����������������ϲ��������ϲ��ܼ���
// ���ң��������Լ��ı������
// �µ�������һ������

    if(!obj1 && !obj2)
    {
        message_vision(CYN"$N"NOR+CYN"�ƺ���˵��ʲô����������ʲô�Ƶ�΢΢Ц��һЦ��ȴ�ֲ�˵���ˡ�\n"NOR,ob);
        return 1;
    }

    if(obj1 && obj1->query("host_id") !=me->query("id") )
    {
        command("say ��"+obj1->query("name")+NOR+CYN"��������ġ�����ô���˱��˵Ķ�����");
        return 1;
    }

    if(obj2 && obj2->query("host_id") !=me->query("id") )
    {
        command("say ��"+obj2->query("name")+NOR+CYN"��������ġ�����ô���˱��˵Ķ�����");
        return 1;
    }

    if( !me->query_temp("hj_find_gem/name") || !me->query_temp("hj_find_gem/id") )
    {
        temp_i=random(5);
        if(temp_i >= sizeof(gem_names) )
            temp_i = sizeof(gem_names) -1;
        gem_name = gem_names[temp_i];
        gem_id = gem_ids[temp_i];

        command("say ������Ѱ��"+gem_name+"���ҽ������ҵĹ��ȵı��");
        me->set_temp("hj_find_gem/name",gem_name);
        me->set_temp("hj_find_gem/id",gem_id);
        command("smile "+me->query("id"));

        gem_npc=new(__DIR__"hj_npc_kill");

        gem_npc->set("delete_time_max",1800);  // �˴���NPC����Сʱ�����
        gem_npc->set("take_gem_npc","yes");
        gem_npc->set("the_gem_for",me->query("id"));
        gem_npc->setme( temp_i );

        temp_i=1+random( HJ_ROOM_AMOUNT );
        gem_rooms=find_object( HJ_DIR +"hj_room"+temp_i);
        if(!gem_rooms) gem_rooms=load_object( HJ_DIR +"hj_room"+temp_i);
        gem_npc->move(gem_rooms);
        if(gem_npc->query("msg")) tell_room(gem_rooms,gem_npc->query("msg"));
        else tell_room(gem_rooms,gem_npc->query("name")+"���˹�����\n");
        return 1;
    }

    my_gem=present(me->query_temp("hj_find_gem/id") , me);
    if(!my_gem)
    {
        command("say �㻹δѰ��"+me->query_temp("hj_find_gem/name")+"����");
        command("pat "+me->query("id"));
        return 1;
    }

// �ɹ�Ѱ�����屦��
    baowu=new(baowu_dir);
    baowu->set("host_id",me->query("id"));
    baowu->setme( 0 );
    baowu->move(me);

    message_vision(CYN"$N"NOR+CYN"�ó�һ��"+my_gem->query("name")+NOR+CYN"�ݸ���"+ob->query("name")+NOR+CYN"��\n",me);
    destruct(my_gem);
    command("idle2");
    message_vision( CYN"$n"NOR+CYN"΢΢һЦ����һ��"+baowu->query("name")+NOR+CYN"�ݸ���$N"NOR+CYN"��\n"NOR, me, ob);

// ������Ʒ������֮������� hj_room1.c ���ٵõ�������ʿJOB��

    baowu = new( __DIR__"hj_obj_ylling" );
    baowu ->set("my_master", me);
    baowu ->set("this_time_mark", me->query_temp("this_time_mark") );
    baowu ->set("long",
        baowu->query("long") + "�������ƺ����Ÿ�ϸϸ�����֣�"+me->query("id") + "\n");
    baowu ->delete("waiting_set");
    baowu ->move(me);

    message_vision( CYN"$n"NOR+CYN"���ó���һ��"+baowu->query("name")+NOR+CYN"�ݸ���$N"NOR+CYN"��\n"NOR,me,ob);
    command( "say ���������о��������������������������ƣ�����Щ���������");
    message_vision(CYN"$N"NOR+CYN"˵�꣬��ӰͻȻ���ʣ���Ȼ�ʹ���ʧ������\n"NOR,ob);
    message_vision(CYN"$N"NOR+CYN"ϸϸ˼���ţ�һʱ�侹Ȼ��ס�ˡ�\n"NOR,me);
    me->start_busy(10+random(10));   // ��ʱ�м��ߵ�æʱ�������й������Ҫ��

    temp_i = 3;
    while( temp_i -- )
    {
        if(random(3))
        {
            baowu = new(__DIR__"hj_npc_kill");
            baowu -> set("killme_by", me->query("id") );
            baowu ->move(environment(me));
            message_vision( "$N�첽���˹�����\n", baowu);
        }
    }

    singing=1; 
// ���������Ӧ���жϣ�����wait delete �Ķ̶�һ������Ա�֤����ִ���κκ��� :)
    remove_call_out("sing_song");
    destruct(this_object());
    return 1;
}
