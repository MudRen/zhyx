//                ��׼��������ʾ��                                   |
// ���þ���Ѱ��ϵ������֮�˳���ͳ�Ƴɼ�������������
// by naihe  2002-11-01
// 03-10-23  ����ͱ���ļ���ͬ���������ȫ���Ĺ��ˣ������ĳ������Ż�
// ���롢�ĸ����ã���JOB��JOB���ѣ�hohoho
// ����д�����ڡ�


#include <ansi.h>
inherit ROOM;
inherit F_SAVE;
#include <ctime_format_func.h>

// ��ʦ������ <mewiz> ָ�������Ƿ����������ȡ��Ʒ����������������� <mewiz> ָ����

// ########################################################
// ########################################################
// ########################################################

#define            HJ_OUTROOM_DATA    "/data/huanjing/outroom_data"
// �洢�ļ�

#define            IS_TEST              0
#define            TEST_AWARD_GXD       1


// ����״̬ʱ��ֻ����ÿ 500 ��÷ֻ�ȡ TEST_AWARD_GXD �㹱�׶ȡ�
// �����ڲ���״̬ʱ��������� ID �жϣ�δ�Ǽǲ�����Ե�ID��
// �� "z_test_id_list.h"  ��  test_id_list  ��δ�Ǽǵ�ID��
// �����¼ log ���Լ����ܵõ�������

// ��ϣ���ڲ���״̬ʱ�������κν�������ֵ set 0.

// ########################################################
// ########################################################
// ########################################################

#include    "z_test_id_list.h"
// ���ļ��ڽ�����һ�� string* ������ test_id_list.


#include     "z_hj_log_func.h"
// ���ļ��ж�����LOG�ļ����ļ�����HJ1_LOG_FILE
// �Լ� hj_log_file(string log_msg) ������
// ���ļ��� ��Ʒת�ô� ��ʹ�� hj_log_file() ����������ֱ��ʹ�� log_file() .


// ������߷�
string
    HighName1 = "��", HighId1 = "--",
    HighName2 = "��", HighId2 = "--",
    HighName3 = "��", HighId3 = "--";

int    HighScore1 = 0, HighScore2 = 0, HighScore3 = 0;


int OkTimes, FailTimes, AllTimes, FindTimes;

string GetAward = "����";


// ���������Ŀ¼�ڵ�һ���۸��ļ�
#include "npc_obj/hj_settings/obj_values.h"

// ��Щ id ��Ҫ����Ϸ�ڵ���ͬ����
// ʹ�� #define �ķ�ʽ���������ᱻ restore() ǿ�ƻָ�������ɸ���ʱ����
// ��ɾ�� .o ���鷳��

#define        all_ids        ([ "dx shuijing":"dx","fx zhishi":"fx","tl shuijing":"tl","hg zhijing":"hg", "qd zhishi":"qd","zh zhihe":"zh","fd zhiqi":"fd","qz zhiqi":"qz", "xr shuijing":"xr","kt shuijing":"kt", "cs zhitong":"cs","dw zhiyi":"dw", "wm guo":"wmg","xr guo":"xrg","tq guo":"tqg","dl guo":"dlg","ys guo":"ysg", "sl guo":"slg", "qt jian":"qtj","lq jian":"lqj","by jian":"byj","yd jian":"ydj", "hj jian":"hjj","nl jian":"nlj","xy jian":"xyj","dh jian":"dhj","bs jian":"bsj", "kf sj":"kfsj","by sj":"bysj","ll sj":"llsj","yd sj":"ydsj","gs sj":"gssj","fh sj":"fhsj","dh sj":"dhsj", "hufeng shi":"hfzs","huanyu shi":"hyzs","luolei shi":"llzs","yindian shi":"ydzs","gunshi shi":"gszs","feihuo shi":"fhs","duohun shi":"dhzs","fuhuo shi":"fhzs" ])


string query_save_file()
{
    return HJ_OUTROOM_DATA;
}

void setlong();

int me_ok( object me )
{
    if( !me || !environment(me) || environment(me) != this_object()
      || query("is_checking") != me->query("id")
      || (me->query_temp("huanjing") != "fail" && me->query_temp("huanjing") != "over")
    )
        return 0;
    return 1;
}

void create()
{
    restore();
    set("short",HIW"�ع�֮·"NOR);
    setlong();
    delete("is_checking");
    // ���һ��Ҫ
    set("no_fight", "1");
    set("no_steal", "1");
    set("no_sleep_room", "1");
    set("invalid_startroom",1);
    set("exits",([
        "out" : __DIR__"room_door_hj",
    ]));
    setup();
}

void init()
{
    if( wizardp(this_player()) )
        add_action("do_mewiz","mewiz");
    add_action("YEAH","YEAH");
    add_action("prize","YEAH!!!");
    add_action("outout", "outout");
    // ��ָֹ��
    add_action("no_do_cmds", ({ "get", "put", "drop" }) );
}

int do_mewiz(string arg)
{
    object me=this_player();
    string f_name, msg;

    if( !wizardp(me) )
        return 0;
    if( !arg )
        arg = ".";
    f_name = LOG_DIR + get_log_file_name() + ".c";
    if( arg == "cklog" )
    {
        if( IS_TEST )
            msg = "�����ǲ���״̬��Ĭ�ϵ�LOG�ļ��ǣ�"+f_name+"\n";
        else
            msg = "����������״̬�����ڵ�LOG�ļ��ǣ�"+f_name+"\n";
        me->start_more_file( f_name );
        write( msg );
        return 1;
    }
    if( arg == "����" || arg == "������" )
    {
        if( GetAward == arg )
            return notify_fail("�����Ѿ�����������ˡ�\n");
        GetAward = arg;
        save();
        return notify_fail("���óɹ������ڿ�ʼ��������������� "+GetAward+" ��ȡ��Ʒ��\n��ע�⣬������ý����ڱ��������غ�ȡ�������ָ�ΪĬ�����á�\n");
    }
    write("���� "+GetAward+" �����ȡ��Ʒ����ָ�� <mewiz ����/������> ������������á�\n����Ĭ�ϵ�LOG�ļ��ǣ�"+f_name+" ��\n��ָ�� <mewiz cklog> ���ٲ鿴����ļ���\n");
    return 1;
}

void reset()
{ 
    ::reset(); 
    set("no_clean_up", 1); 
}

int valid_leave(object me, string dir)
{
    object *all_mine;
    int temp, i;

    if( query("is_checking") == me->query("id") )
        return notify_fail("�������ڼ�����ĵ÷֣����Ե����뿪��\n");
    all_mine = deep_inventory(me);
    if( all_mine && sizeof( all_mine ) > 0 )
    {
        for(i=0;i<sizeof(all_mine);i++)
        {
            if( all_mine[i] ->query("hj_game") )
            {
                temp = 1;
                break;
            }
        }
    }
    if(temp)
        return notify_fail( HIR"�����ϻ�Я���Żþ���ص���Ʒ�����ȼ���÷����뿪��\n"
            "����ִ��Ҫ�뿪����ʹ�� outout ָ���ô��ĵ÷ּ�����Я���Ļþ���Ʒ���������\n"NOR );
    if ( me->query_temp("huanjing") == "fail" || me->query_temp("huanjing") == "over" )
        return notify_fail(HIR"��δ�����������Ϸ�÷֣����ȼ���÷����뿪��\n"
            "����ִ��Ҫ�뿪����ʹ�� outout ָ���ô��ĵ÷ּ�����Я���Ļþ���Ʒ���������\n"NOR);
    if ( me->query_temp("hj_score") )
        return notify_fail(HIR"��δ������ĵ÷�ȫ���ҽ������ȶԽ�������뿪��\n"
            "����ִ��Ҫ�뿪����ʹ�� outout ָ���ô��ĵ÷ּ�����Я���Ļþ���Ʒ���������\n"NOR);
    return ::valid_leave(me, dir);
}

int outout()
{
    object me = this_player(), *all_mine;
    int i;

    all_mine = deep_inventory(me);
    if( all_mine && sizeof( all_mine ) > 0 )
    {
        for(i=0;i<sizeof(all_mine);i++)
        {
            if( all_mine[i] ->query("hj_game") )
                destruct( all_mine[i] );
        }
    }
    me->delete_temp("hj_score");
    me->delete_temp("huanjing");
    message_vision( HIR"\n$N"HIR"ʹ����ǿ��ָ��뿪�����\n"NOR, me );
    me->move( query("exits/out") );
    message_vision( "$N���˹�����\n",me );
    return 1;
}

int no_do_cmds()
{
    if( !wizardp( this_player() ) )
    {
        write("�������㲻����ʹ�����ָ�\n");
        return 1;
    }
    return 0;
}

string get_TOP_pic()
{
    string c1 = HIB, c2 = HIY, c3 = HIC, c4 = HIG;

    return sprintf(c1+"
 �����������ש��������������������ש�������������
 ��"+c2+"����ܷ�"+c1+"��"+c2+"%|20s"+c1+"��"+c2+"%|12d"+c1+"��
 �ǩ��������贈�������������������贈������������
 ��"+c3+"��ߵ÷�"+c1+"��"+c3+"%|20s"+c1+"��"+c3+"%|12d"+c1+"��
 �ǩ��������贈�������������������贈������������
 ��"+c4+"���Ч��"+c1+"��"+c4+"%|20s"+c1+"��"+c4+"%6|d /Сʱ"+c1+"��
 �ǩ��������ߩ����ש��������ש����ߩ��ש���������
 ��"HIW"���˴�%|8d"+c1+"��"HIC"ʤ%|6d"+c1+"��"HIM"��%|6d"+c1+"��"HIY"��%|6d"+c1+"��
 �����������������ߩ��������ߩ��������ߩ���������\n"NOR, 

    HighName1+"("+HighId1+")", HighScore1,
    HighName2+"("+HighId2+")", HighScore2,
    HighName3+"("+HighId3+")", HighScore3,
    AllTimes, OkTimes, FailTimes, FindTimes);
}

void setlong()
{
    set("long", "
            "HIW"�� �� �� �� ʵ ֮ · ��
"NOR+get_TOP_pic()+HIW"
      ���ɣ�̤�ϻع���ʵ֮·����������������
    �þ�֮�£��������������߳����㽫�ع�����
  �������õ�����֮�أ��㽫��ǵ�������Ӧ�õ����ڡ�
"NOR"
  ������ĵ÷���һ���Ϸ������< "HIG"YEAH"NOR" / "HIY"YEAH!!!"NOR" >\n");
}


// ####################################################
// ############## �����Ǽ���÷ֵĺ��� ################
// ####################################################

int YEAH()
{
    int temp_score;
    object me = this_player();

    temp_score = me->query_temp("hj_score");

    if( !me->query_temp("huanjing") && temp_score )
        return notify_fail("��ĵ÷��Ѿ�������ˡ������� <YEAH!!!> ָ���ѯ�콱��\n");

    if( me->query_temp("huanjing") != "fail" && me->query_temp("huanjing") != "over" )
    {
        me->delete_temp("hj_score");
        return notify_fail("���ع���ʵ��ĪҪͣ���þ���\n");
    }

    if( query("is_checking") )
        return notify_fail("���������� "+query("is_checking")+" �ĵ÷֣����Եȡ�\n");
    set("is_checking", me->query("id") );

    // ��Ϸ�÷ֵ�����߼�¼
    message_vision(HIW"\n$N��ʼ�����Լ��ĵ÷֡���\n\n"NOR,me);
    message_vision(HIC"$N"HIC"����Ϸ�ڵ÷�Ϊ��"HIY+temp_score+HIC" �㡣\n"NOR, me);

    if( temp_score > HighScore2 )
    {
        if( me->query_temp("huanjing") == "fail" )
            message_vision(HIY"\n$N"HIY"����Ϸ����÷ֳ�������߼�¼��ֻ��ϧ��ʧ�ܹ����ġ�\n"NOR,me);
        else
        {
            message_vision(HIY"\n$N"HIY"��������Ϸ����÷ֵĵ�����߼�¼��\n"NOR, me);
            me->set("huanjing2003/gift", "��������÷ֵ�����߼�¼");
            HighScore2 = temp_score;
            HighName2 = me->query("name");
            HighId2 = me->query("id");
            setlong();
        }
    }
    write(HIW"\n���ڼ�����Я���� ���������Ʒ �ӷ֡���\n"NOR);
    remove_call_out("score_tools");
    call_out( "score_tools", 2, me);
    return 1;
}

void score_tools( object me )
{
    if( !me || !me_ok(me) )
    {
        delete( "is_checking" );
        return;
    }

    tell_object( me, "��ĸ��ೣ�������Ʒ�ӷ����£�\n\n");
    // ������һ�������µ��ж���д����Ȼ��ԭ�ȵĺ�N����Դ������������
    // ����Ϊ������Ч���������գ��Ͱ���ô����
    remove_call_out("score_tools_go");
    call_out( "score_tools_go", 1, me, 0, 0);
}

void score_tools_go( object me, int score, int hj_obj_amount )
{
    object *inv_me, temp;
    int i, temp_score;
    string temp_id;

    if( !me || !me_ok(me) )
    {
        delete( "is_checking" );
        return;
    }

    inv_me = all_inventory(me);
    if(inv_me && sizeof(inv_me) > 1)
    {
        for(i=0;i<sizeof(inv_me);i++)
        {
            temp = inv_me[i];

            if( !temp ->query("hj_game/obj") )
                continue;

            temp->set("value",0);
            temp_id = temp -> query("id");

            if( !all_ids[temp_id] || !all_values[all_ids[temp_id]] )
                continue;

            hj_obj_amount ++;
            temp_score = all_values[all_ids[temp_id]] / 3;
            if( temp_score < 1 ) temp_score = 1;
            tell_object( me, sprintf("һ%s %s(%s) ���ɻ�� %d ����Ϸ�÷֡�\n",
            temp->query("unit"),temp->query("name"),temp->query("id"),temp_score));
            destruct(temp);
            score += temp_score;
            remove_call_out("score_tools_go");
            call_out( "score_tools_go", 1, me, score, hj_obj_amount );
            return;
        }
    }

    message_vision("\n$N���г������ "+hj_obj_amount+" �����÷��� "+score+" �㡣\n", me);
    me->add_temp("hj_score", score );
    tell_object( me, HIW"\n���ڼ�����Я���� ������Ʒ �ӷ֡���\n"NOR);
    remove_call_out("score_special_tools");
    call_out("score_special_tools", 2, me );
}

void score_special_tools( object me )
{
    if( !me || !me_ok(me) )
    {
        delete( "is_checking" );
        return;
    }

    tell_object( me, "��ĸ������������Ʒ�ӷ����£�\n\n");
    // ͬ�ϱ�һ�����Ұ�������������
    remove_call_out("score_sp_tools_go");
    call_out( "score_sp_tools_go", 1, me, 0, 0);
}

void score_sp_tools_go( object me, int score, int hj_obj_amount )
{
    object *inv_me, temp;
    int i, temp_score;
    string temp_id, temp_msg;

    if( !me || !me_ok(me) )
    {
        delete( "is_checking" );
        return;
    }

    inv_me = all_inventory(me);
    if(inv_me && sizeof(inv_me) > 1)
    {
        for(i=0;i<sizeof(inv_me);i++)
        {
            temp = inv_me[i];
            temp_msg = "none";

            if( !temp ->query("hj_game/obj") )
                continue;

            hj_obj_amount ++;

            temp->set("value",0);
            temp_id = temp -> query("id");

            // ���ұ������ӷ�
            if(temp_id == "tmxk yyf" || temp_id == "xlsq szl"
              || temp_id == "wm slzj" || temp_id == "sxzy dsg"
            )
            {
                // ���Ǳ��˵ģ������� ���١��ı�ǣ�ֻ��һ����(��������˵)��
                if( !temp -> query("host_id")
                  || temp->query("host_id") != me->query("id")
                  || temp->query("fake")
                )
                {
                    temp_score = 500;
                    temp_msg = "������Ҫ��Ѱ��";
                }
                // ����͸߷�
                else
                {
                    // ��������Ϊ�˷�ֹ�� ��������ۻ� -> һ���Դ����� �ķ���������߷ּ�¼�� :)
                    // ��Ȼ��������Ҳ�У�������ɿ��ܶ��ˣ��Ǻǡ�
                    // ����ϸ����Ϣ���Կ� _qxd_.c �� 3 �����ļ�
                    if( temp->query("this_time_mark") !=
                        me->query_temp("this_time_mark") )
                    {
                        temp_score = 500;
                        temp_msg = "��������һ��Ҫ��Ѱ��";
                    }
                    else
                    {
                        temp_score = 1500;
                        temp_msg = "�������";
                        FindTimes ++;
                    }
                }
            }

            // ������ɲ��ֵĶ���ӷ�
            if(temp_id=="tm shen" || temp_id=="sz zuoyi" || temp_id=="sz youyi"
              || temp_id=="lq shou" || temp_id=="jy lei" || temp_id=="mh xin"
              || temp_id=="sl jian" || temp_id=="dz shi" || temp_id=="rr shao"
              || temp_id=="hongse baoshi" || temp_id=="lanse baoshi" || temp_id=="lvse baoshi"
            )
            {
                // ���Ǳ��˵ģ��۷֣�
                if( !temp->query("host_id")
                  || temp->query("host_id") != me->query("id")
                )
                {
                    temp_score = -200;
                    temp_msg = "������Ҫ��Ѱ��";
                }
                // ��������һ�㽱����
                else
                {
                    temp_score = 200;
                    temp_msg = "�������";
                }
            }
            // ����Ȩ�ȼӷ�
            if( member_array( temp_id, ({ "manye quanzhang", "mengli quanzhang",
                "aiyao quanzhang", "shanguai quanzhang", "juren quanzhang",}) ) != -1
            )
            {
                temp_msg = "���ص�";
                temp_score = 50;
            }
            // ���屦��ӷ�
            if( member_array( temp_id, ({ "manye baowu", "mengli baowu",
                "aiyao baowu", "shanguai baowu", "juren baowu",}) ) != -1 )
            {
                temp_msg = "����";
                temp_score = 100;
            }
            // ������һ��ɾ�������� 1 �֡�
            if(temp_msg == "none" )
            {
                temp_msg = "�����ô���";
                temp_score = 1;
            }
            tell_object( me, sprintf("һ%s "+temp_msg+" %s(%s) ���ɻ�� %d ����Ϸ�÷֡�\n",
                temp->query("unit"),temp->query("name"),temp->query("id"),temp_score) );
            score += temp_score;
            destruct(temp);
            remove_call_out("score_sp_tools_go");
            call_out( "score_sp_tools_go", 1, me, score, hj_obj_amount );
            return;
        }
    }
    message_vision("\n$N����������Ʒ "+hj_obj_amount+" �����÷��� "+score+" �㡣\n", me);
    me->add_temp("hj_score", score );
    tell_object( me, HIW"\n���ڼ���������÷֡���\n"NOR);
    remove_call_out("score_all");
    call_out("score_all", 2, me );
}


void score_all( object me )
{
    object *inv_me, temp;
    int i, hj_obj_amount, score, temp_score, e_time,o_time, g_time, xiaolv;
    string temp_id, temp_msg, msg = "";

    if( !me || !me_ok(me) )
    {
        delete( "is_checking" );
        return;
    }

    tell_object( me, "��������ӷ��Լ����÷����£�\n\n");

    // ����ӷ�
    temp_score = me->query("huanjing2003/lv") * 20;  // ��50��Ϊ20   naihe 05-9-7 10:14
    if( temp_score == 450 )  // 9 ������
        temp_score = 200;                            // ��500��Ϊ200   naihe 05-9-7 10:14
    msg += "����÷֣�" + temp_score+" �㡣\n";
    score += temp_score;
    temp_score = 0;

    // ��Ϣ�ӷ�
    temp_score = ( me->query_temp("hj_hp_max")
            -( me->query_temp("hj_hp_max") - me->query_temp("hj_hp") ) ) / 10;
    if( temp_score < 0 ) temp_score = 0;
    msg += "��Ϣ�÷֣�" +temp_score+ " �㡣\n";
    score += temp_score;
    temp_score = 0;

    // �����ӷ�
    temp_score = me->query_temp("hj_game_mepower") / 2;
    if( temp_score < 0 ) temp_score = 0;
    msg += "�����÷֣�"+ temp_score +" �㡣\n";
    score += temp_score;
    temp_score = 0;

    me->add_temp("hj_score", score );
    tell_object( me, msg );

    // ������ϣ�����Ч��
    score = me->query_temp("hj_score");
    e_time = me->query_temp("hj_enter_time");
    o_time = me->query_temp("hj_out_time");
    if( e_time && o_time && o_time > e_time ) g_time = o_time - e_time;

    if( g_time )
    {
        xiaolv = score * 3600 / g_time;
        msg=sprintf("��Ϸʱ�乲%dСʱ%d��%d�룬�������㣬$N"HIC"�Ļþ���Ϸ�÷�Ч��ΪÿСʱ %d �㣡",
            g_time / 3600, g_time % 3600 / 60, g_time % 3600 % 60, xiaolv);
    }
    else
    {
        xiaolv = 0;
        msg = "����$N"HIC"û�н�����˳���Ϸ��ʱ���¼���޷�����Ч�ʡ�";
    }

    message_vision(HIC"\n$N"HIC"�����յ÷��ǣ�"+score+" �㣡\n"+msg+"\n\n"NOR, me);
    if( score > HighScore1 )
    {
        if( me->query_temp("huanjing") == "fail" )
            message_vision(HIY"$N"HIY"�����յ÷ֳ�������߼�¼��ֻ��ϧ��ʧ�ܹ����ġ�\n"NOR, me);
        else
        {
            message_vision(HIY"$N"HIY"�������ܳɼ�����߼�¼������\n"NOR, me);
            me->set("huanjing2003/gift", "�����ܳɼ���߼�¼");
            HighScore1 = score;
            HighName1 = me->query("name");
            HighId1    = me->query("id");
            setlong();
        }
    }

    if( xiaolv > HighScore3 )
    {
        if( me->query_temp("huanjing") == "fail" )
            message_vision(HIY"$N"HIY"��Ч�ʳ�������߼�¼��ֻ��ϧ��ʧ�ܹ����ġ�\n"NOR,me);
        else
        {
            message_vision(HIY"$N"HIY"������Ч����߼�¼��\n"NOR, me);
            me->set("huanjing2003/gift", "����Ч����߼�¼");
            HighScore3 = xiaolv;
            HighName3 = me->query("name");
            HighId3 = me->query("id");
            setlong();
        }
    }

    // ʧ�ܷ�
    if(me->query_temp("huanjing") == "fail")
    {
        FailTimes ++;
        message_vision(HIR"���ź���$N"HIR"��ʧ�ܹ����ģ����е÷ֽ����ϡ�\nף$N"HIR"�´��ܹ�ȡ�úóɼ�����ȡ����Ľ�����\n"NOR,me);
        // ���ǲ���ʱ������Ҫ��ID LIST �ڵ���Ҳż��� LOG.
        if( !IS_TEST || member_array( me->query("id"), test_id_list ) != -1 )
            hj_log_file( sprintf("\n��( %s - %s )\n��  %s(%s) ����Ϸ %d ʱ %d �� %d �룬�÷� %d (ʧ�ܣ��÷�����)��\n",
                e_time ? ctime_format( e_time ) : "�޽���ʱ���¼",
                o_time ? ctime_format( o_time ) : "���˳�ʱ���¼",
                me->query("name"), getuid(me), 
                g_time ? g_time / 3600 : 0,
                g_time ? g_time % 3600 / 60 : 0,
                g_time ? g_time % 3600 % 60 : 0,
                me->query_temp("hj_score") ));

        me->delete_temp("hj_score");
    }
    else
    {
        OkTimes++;

        // ���ǲ���ʱ������Ҫ��ID LIST �ڵ���Ҳż��� LOG.
        // �ɹ����LOGʹ��ʵ��Բ�α�ǣ��鿴����������
        // ��������LOG�����˱�ǣ���Ϊ���ڲ鿴ʱ������LOG�ֿ��������㡣
        if( !IS_TEST || member_array( me->query("id"), test_id_list ) != -1 )
            hj_log_file( sprintf("\n��( %s - %s )\n��  %s(%s) ����Ϸ %d ʱ %d �� %d �룬�÷� %d ��%s\n",
                e_time ? ctime_format( e_time ) : "�޽���ʱ���¼",
                o_time ? ctime_format( o_time ) : "���˳�ʱ���¼",
                me->query("name"), getuid(me), 
                g_time ? g_time / 3600 : 0,
                g_time ? g_time % 3600 / 60 : 0,
                g_time ? g_time % 3600 % 60 : 0,
                me->query_temp("hj_score"),
                xiaolv ? "(Ч�ʣ�"+ xiaolv +" / Сʱ )" : "(Ч��δ֪)") );


        if( score > 10000 )
        {
            message_vision("$N�ĵ÷��� "+score+" �㣬���������ޣ��� 10000 ����㡣\n", me);
            me->set_temp("hj_score", 10000 );
        }

        message_vision(HIW"��ϲ$N"HIW"�ɹ����������õ����е���Ϸ������������ <YEAH!!!> ָ���ѯ��Ʒ�һ���\n"NOR,me);
    }

    me->delete_temp("huanjing");

    // ��¼����ұ��εļ��ܡ�������
    // �����ݽ�����һ�ν�����Ϸʱ�����ǵ��ж�ʹ�ã�
    // ���ﲻ���κ��жϡ�

    me->set("huanjing2003/last_power", me->query_temp("hj_game_mepower") );
    me->set("huanjing2003/last_skills_name", me->query_temp("hj_game_skills") );
    me->set("huanjing2003/last_skills_lv", me->query_temp("hj_game_damages") );
    // ��ʹ���û�и�����ֵ��Ҳ��ֻ��������� 0 ���ˡ����Ǳ߻ᴦ��

    me->save();

    delete("is_checking");
    AllTimes ++;
    setlong();
    save();
    // ֻ���������ʱ��� save() .

    if( IS_TEST && !TEST_AWARD_GXD )
    {
        message_vision(HIY"\n���������ǲ����ڼ䣬����û���κν�����$N"HIY"�ĵ÷ֱ�����ˡ�\n\n"NOR, me);
        me->delete_temp("hj_score");
    }

    if( IS_TEST && member_array( me->query("id"), test_id_list ) == -1 )
    {
        message_vision(HIY"\n���������ǲ����ڼ䣬����$N"HIY"û�б����μӲ��ԣ�$N"HIY"�ĵ÷ֱ�����ˡ�\n\n"NOR, me);
        me->delete_temp("hj_score");
    }
}


// ############## �����Ǽ���÷ֵĺ��� ################

// ####################################################
// ############## ��������ȡ��Ʒ�ĺ��� ################
// ####################################################

#include "z_gameover_hj.h"

