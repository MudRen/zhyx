//                ��׼��������ʾ��                                   |
// �þ���ңԶ��˵֮��Ե���������� ����������ڼ������Ƿ� robot.  grin~
// ���κ�����дROBOT�ĳ�ˮƽ��ֻ���뵽������д������֪��������������
// ������ robot ���ش� grin~
// ROBOT CHECK ������ 2002 �������д�ɣ�������ֱ�Ӹ��ƹ����õġ�

// by naihe  2003-10-22  ��ï��

#include <ansi.h>
inherit NPC;

#include <set_del_color.h>
string ask_quest_again();
mapping get_question(int times);
string get_flag(string this_times);


#define        IS_TEST            0
// ��Ҫ���Ծ͸� 0 �
// ����ʱʹ��  <testquest ID> �������ԡ�

#define        PIC_NUMBER        40
#define        AWARD_SCORE        30


int me_ok(object me)
{
    if( !me || me->query_temp("hj_hp") < 1 || me->query_temp("huanjing") != "start"
      || !environment(me) || !environment(me)->query("room_mark")
          || !query("this_time_mark")
      || query("this_time_mark") != me->query_temp("this_time_mark") )
        return 0;

    return 1;
}

void create()
{
    set_name( "������", ({ "mengmian ren", "mmr" }) );
    set("long", "����һ��������������ˣ�ɤ��ɳ�ƣ�һ��������������ӡ�\n");
    set("hj_game/npc", "robot_checker");
    set("gender","����");
    set("age", 41);
    set("no_refresh",1);
    set("inquiry",([
        "question" : (: ask_quest_again :),
        "����"     : (: ask_quest_again :),
    ]));

    setup();
}

void init()
{
    add_action("do_look", "look");
    add_action("do_ans", "ans");
    add_action("do_test", "testquest");
}

int do_test( string arg )
{
    object who;

    if( !IS_TEST ) return 0;

    if( query("wait_ans") ) 
        return notify_fail("�������ڽ��в��ԡ�\n");

    if( !arg ) return notify_fail("Ҫ��˭����������ԣ�\n");

    message_vision( "$N����$n˵��������"+arg+"���в������⡣��\n", this_player(), this_object() );
    command( "ok" );

    who = present( arg, environment(this_object()) );
    if( !who )
    {
        command("say ����˲�������Ү��");
        return 1;
    }

    delete("ans_error");
    delete("quest_ok");
    delete("wait_ans");
    delete("ans_over");

    set("checking_player", who );
    remove_call_out("start_check");
    remove_call_out("delete_me");
    call_out("start_check", 1);
    return 1;
}


int do_ans( string arg )
{
    object me = this_player();
    int player_ans;

    if( query("ans_over") ) return 0;

    if( !query("checking_player") || me != query("checking_player")
        || !query("this_time_mark")
        || query("this_time_mark") != me->query_temp("this_time_mark") )
        return notify_fail("����ʲô�£��ֲ������㡣\n");

    if( !arg )
    {
        message_vision("$N����$n����˵��������֪���ˣ��������Ͳ������������\n", me, this_object() );
        command( "kick "+me->query("id") );
        command( "say ��˵�������������ϸ�㣡");
        return 1;
    }


    message_vision("$N����$n����˵��������֪���ˣ�����λ���� "+arg+" ����\n", me, this_object() );

    if( !query("wait_ans") )
    {
        command("say ��ʲô���Ҷ���û���㣡");
        return 1;
    }

    if( sscanf( arg, "%d", player_ans ) )
    {
        if( player_ans == query("quest_ans") )
        {
            command( "consider" );
            set("quest_ok", 1);
            remove_call_out("delete_me");
            call_out("delete_me", 1);
            return 1;
        }
        command( "hmm " + me->query("id") );
        if( !query("ans_error") )
        {
            set( "ans_error", 1);
            command("say ����ϸ�㣡��������������������û����Ͷ�����һ��(ask mengmian ren about ����)������");
            return 1;
        }
        command( "faint "+me->query("id") );
        set("ans_over", 1);
        remove_call_out("delete_me");
        call_out("delete_me", 1);
        return 1;
    }

    command("say ��˵������ϸ�㣡");
    return 1;
}


void delete_me()
{
    object me = query("checking_player"), ob = this_object();
    int hp;

    if( IS_TEST )
    {
        message_vision("\n", this_object() );
        if( query("quest_ok") )
            command("say �����ش���ȷ��");
        else command("say ���ˣ��� "+query("quest_ans")+" �Ŷԣ�");
        delete("wait_ans");
        return;
    }

    if( !me || !me_ok(me) )
        message_vision("$N����������һ�£������뿪�ˡ�\n", ob );

    else if( query( "quest_ok" ) )
    {
        command( "say ��"+delcolor( me->query("name") )+"�������ģ�лл���ˣ���\n");
        message_vision("$n������$N��ͷ��������뿪�ˡ�\n", me, ob );
        hp = AWARD_SCORE + random( AWARD_SCORE );
        me->add_temp("hj_score", hp );
        tell_object( me, HIR"��Ϸ��ʾ����ĵ÷������� "+hp+" �㣡\n"NOR);
    }
    else
    {
        ob->move( environment(me) );
        message_vision( "$n����$N��ͷ������������д���������ô�򵥵����ⶼ���ᣬ�÷�����\n˵�գ�$n����$N����һ�ţ�$Nֻʹ���໴�С�\n$n��������Ҷ��������ˣ��� "+query("quest_ans")+" �������$n˵�꣬���ߵ��뿪�ˣ�\n", me, ob);
        tell_object( me, HIR"��Ϸ��ʾ�������Ϣ��󽵵��ˣ�����\n"NOR );

        hp = me->query_temp("hj_hp");
        hp = hp / 5;
        if( hp < 1 ) hp = 1;
        me->set_temp("hj_hp", hp );
    }

    destruct( ob );
}

int do_look(string arg)
{
    if( !arg || !id(arg) ) return 0;

    write( query("long") );
    return 1;
}


string ask_quest_again()
{
    object me = this_player();
    if( me != query("checking_player") )
        return "�������¡�";

    if( !query("wait_ans") )
        return "��ʲô����������Ҫ��ʲô�ˡ�";

    command("say ������㰡��");
    return query("quest");
}


void start_check()
{
    mapping question_info;
    object me;
    string shows_all, shows_color, shows_flag;

    if( !environment(this_object() ) ) return;

    me = query("checking_player");
    if( !me || ( !IS_TEST && !me_ok(me) ) ) return;

    question_info = get_question( PIC_NUMBER );

    message_vision("ֻ��һ��$n����ææ�����˹�����ֱ�嵽$N��ǰ���ſھ�����һ�����⡣\n",
        me, this_object() );

    tell_object( me, query("name")+"˵������"+me->query("name")+"������һ������������㣬����"HIR"���Ҫ���������ڻش�"NOR"�ҡ���\n");

    tell_object( me,  question_info [ "shows_all" ] );
    tell_object( me,  query("name")+"˵�������ҿ������� "+question_info[ "shows_color" ] +" �����ɫ�� "+question_info[ "shows_flag" ] + " ͼ����������ܸ���������ʲôλ���𣿡�\n");
    tell_object( me,  query("name")+"����˵�������������������������λ�ø����Ҿ����ˡ���(ans ����)\n");
    tell_object( me,  query("name")+"�����䷳��˵�����������û���壬��������ң����ظ�һ�Ρ���(ask mengmian ren about ����)\n");

    set( "quest", question_info[ "shows_all" ] + "\n��ɫ��"+ question_info[ "shows_color" ]+" ͼ����"+question_info[ "shows_flag" ] + " ����ش�����λ�ã�����������<ans ����>����\n" );
    set( "quest_ans", question_info[ "answer" ] );
    set("wait_ans", 1);
    remove_call_out("delete_me");
    call_out("delete_me", 180 );
}

mapping get_question(int times)
{
    string
*show=({ }),
*flags=({"��","��","��","��","��","��","��","��","��","��","��","��",}),
flag,
*cls=({HIR,HIC,HIG,HIY,HIW,HIM,}),
cl,
*bcls = ({HBRED,HBCYN,HBGRN,HBYEL,HBWHT,HBMAG,}),
bcl,
temp,
shows = "  ";

    string real_flag;
    int i,j,answer,temp_hh;

    if(!times || times < 5 || times > 100)
        times = 100;

    j = random( 6 );
    flag = flags[random(sizeof(flags))];
    cl = cls[ j ];
    bcl = bcls[ j ];

    real_flag = cl+flag+NOR;

    for(i=0;i<times;i++)
    {
        temp = get_flag(real_flag);
        show += ({ temp });
    }

    answer = 1+random(times);

    show[ answer-1 ] = real_flag;

    shows += "\n";
    for(i=0;i<sizeof(show);i++)
    {
        temp_hh ++;
        shows += show[i];
        if( temp_hh >= PIC_NUMBER / 2 )
        {
            temp_hh = 0;
            shows += "\n";
        }
    }
    shows += "\n\n";

    return ([ "shows_color": bcl+"    "+NOR,"shows_flag": flag+NOR,"shows_all" : shows,"answer":answer ]);

/************************************************
 ��ʽ˵������Ҫ���ñ�����ʱ����Ӳ���������������
 ����ֵԪ��˵����
 shows_color :  �����ʾ����ɫ
 shows_flag  :  �����ʾ��ͼ��
 shows_all   :  �����ʾ����ͼ
 answer      :  ��ȷ��

��ʾ���̣�
1���ȵõ��˺�������ֵ��
mapping test = SHOOTING_D->get_question(random(100));

2���ڵ��ö˲���������ʾ����㣺
string shows_all = test[ "shows_all" ];
string shows_color = test[ "shows_color" ];
string shows_flag = test[ "shows_flag" ];
int answer = test[ "answer" ];

write( shows_all );
write("��ε���ɫ�ǣ�"+shows_color+"��ͼ���ǣ�"+shows_flag+"��\n");

3����ȷ�𰸣��� ��ͼ������ȷλ�ã�����answer��ֵ��

*************************************************/

}

string get_flag(string this_times)
{
    string
*flags=({"��","��","��","��","��","��","��","��","��","��","��","��",}),
temp_flag,
*cls=({HIR,HIC,HIG,HIY,HIW,HIM,}),
temp_cls,
temp_wahaha;

    temp_wahaha = cls[random(sizeof(cls))] + flags[random(sizeof(flags))]+NOR;

    while( temp_wahaha == this_times )
        temp_wahaha = cls[random(sizeof(cls))] + flags[random(sizeof(flags))]+NOR;

    if( !random(2) ) temp_wahaha += " ";

    return temp_wahaha;
}
