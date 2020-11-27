//                ��׼��������ʾ��                                   |
// �þ����� NPC������ʦ
// by naihe  2003-11-05  ��ï��
// ��ʯ��Ҫ��̫�ߣ����͵� 05-9-1 14:43

#include <ansi.h>
#include <errs_func.h>
// �����и� errs() ���� notify_fail() ���� write(msg), return 1;
inherit NPC;


#include "hj_settings/room_amount_hj.h"
#define        MY_ROOM_MARK        10
        // ��NPC�������� HJ ���ֶ��������䴦����Ч
#include "zj_lm_tarder_prefunc.h"


#define        SXF            20
        // �۸񣬼�������

void create()
{
    set_name( "����ʦ", ({ "zhujian shi", "shi" }) );
    set("nickname", HIW"�⽣���� ���и���"NOR );

    set("long", "����һλ���վ�տ������ʦ��ר�Ӹ�����ལ�������⡣
=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    ��ĳ�����ĳ� "GRN"��֮ͭ��"NOR"�� <zj qtj ����ID>
    ��ĳ�����ĳ� "HIW"����֮��"NOR"�� <zj byj ����ID>
    ��ĳ�����ĳ� "HIY"�ƽ�֮��"NOR"�� <zj hjj ����ID>
    ��ĳ�����ĳ� "HIW"����֮��"NOR"�� <zj lqj ����ID>
    ��ĳ�����ĳ� "HIM"ӯ��֮��"NOR"�� <zj ydj ����ID>
    ��ĳ�����ĳ� "HIY"����֮��"NOR"�� <zj nlj ����ID>
    ��ĳ�����ĳ� "HIW"Ѹ��֮��"NOR"�� <zj xyj ����ID>
    ��ĳ�����ĳ� "HIB"���֮��"NOR"�� <zj dhj ����ID>
    ��ĳ�����ĳ� "HIR"��ʤ֮��"NOR"�� <zj bsj ����ID>
�����ⱦʯ 2 �ţ����þ��÷� "+SXF+" �� / �Ρ�

�޲�ĳ��������֮ʹ�ô����ָ�����<zj up ����ID>
�����ⱦʯ 1 �ţ��þ��÷� "+(SXF/2)+" �� / �Ρ�
=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
    set("gender","����");
    set("age",35);
    set("per",19);
    set("attitude","friendly");
    set("no_refresh",1);
    set("hj_game/npc","zhujian");

    setup();
}

void init()
{
    add_action("do_zhujian", ({ "zhujian", "zj" }) );
}

int do_zhujian( string arg )
{
    object me = this_player(), bs1, bs2, bs3, *all_mine, sword;
    string sword_id, type, *list, t;
    int i, set, score_need;

    if( !ob_ok() || !me_ok(me) ) return 0;
    if( me->is_busy() || me->query_temp("hj_need_waiting") )
        return errs("�㻹æ���ء�\n");

    if( !arg || sscanf( arg, "%s %s", type, sword_id ) != 2 )
        return errs("������������(look zhujian shi)��\n");

    if( query("working") )
        return errs("���⻹�е㹤��û��ɣ����Ե�һ����ɡ�\n");

    list = ({ "qtj","lqj","byj","ydj","hjj","nlj","xyj","dhj","bsj"});
    // �����˳��� hj_obj_weapon.c ���˳����һ���ġ�

    set = member_array( type, list );
    if( set == -1 && type != "up" )
        return errs("��������첻�� \""+type+"\" ���ֽ����㻹����������ɡ�\n");

    sword = present( sword_id, me );
    if( !sword ) return errs("���û���������Ľ�������Ϊ�����Ǹ�ʲô�κΰ�������ƾ�ձ�ѽ����㣿\n");
    if( sword->query("hj_game/obj") != "sword" )
        return errs( sword->query("name")+"���ǿ�������Ľ�����\n");
    // ����ǡ�����֮���������ģ��ǡ���������������ʶ

    score_need = (type == "up" ? SXF/2 : SXF);
    if( me->query_temp("hj_score") < score_need +1 )
        return errs("�������޷��ģ����ǲ�Ҫ���Ҫ��ĺã���ʲô���ͽ������ðɡ�\n");

    // ok. up ��
    if( type == "up" )
    {
        if( sword->query("use_times") >= sword->query("real_use_times") )
            return errs("�⽣�úõģ��������ú��أ����ǲ������˰ɡ�\n");
        all_mine = all_inventory(me);
        // ������Ͽ϶��н������ؽ��� !all_mine ���ж�

        /*
        for(i=0;i<sizeof(all_mine);i++)
        {
            // ���ⱦʯ
            if( all_mine[i]->id("baoshi")
              && all_mine[i]->query("hj_game/obj") == "other" )
            {
                if( !bs1 ) bs1 = all_mine[i];
                else if( !bs2 ) bs2 = all_mine[i];
                else { bs3 = all_mine[i]; break; }
            }
        }
        if( !bs1 || !bs2 || !bs3 )
            return errs("�⡭������Ҫ���ű�ʯ������󲻹��ɡ�\n");
        destruct( bs1 );
        destruct( bs2 );
        destruct( bs3 );
        */
        // ��Ϊ���ⱦʯһ�ż���
        for(i=sizeof(all_mine)-1; i>=0; i-- )
        {
            if( all_mine[i]->id("baoshi")
              && all_mine[i]->query("hj_game/obj") == "other"
            )
            {
                bs1 = all_mine[i];
                break;
            }
        }
        if( !bs1 )
            return errs("����Ҫһ�ű�ʯ�������û�аɡ�\n");
        destruct( bs1 );
        // ȫ��OK���������ü�������
        me->add_temp("hj_score", -score_need );
        me->start_busy(1);
        sword->set("use_times", sword->query("real_use_times") );
        if( sword->query("use_times") < 1 ) sword->set("use_times", 1);
        t = NOR+CYN;
        message_vision( sprintf(
            CYN"$N%s�ó�һ%s%s%s�ݸ���$n%s��˵�������鷳����������⽣����\n"
            "$N%s˵�գ����ó���һ�ű�ʯ�������˵�ʲô��һ��������$n%s��\n"
            "ֻ��$n%s�ӹ��˽�����������ֻŪ�˼��£��Ͱ����ݸ���$N%s��\n"
            "$n%s˵�������������⽣�Ѿ��޺��ˣ���֤���á���\n"NOR,
                t, sword->query("unit"), sword->query("name"), t, t,
                t, t,
                t, t,
                t), me, this_object() );
        return 1;
    }
    // ��ô���ǻ����
    // ̫�õĲ���(ʹ���˺ܶ�ε�)
    if( sword->query("use_times") < sword->query("real_use_times")/2 )
        return errs("�⽣�пڶ����ˣ��㻹����������ɡ�\n");
    /*
    bs1 = present( "red baoshi", me );
    bs2 = present( "green baoshi", me );
    bs3 = present( "blue baoshi", me );
    if( !bs1 || bs1->query("hj_game/obj") != "other"
      || !bs2 || bs2->query("hj_game/obj") != "other"
      || !bs3 || bs3->query("hj_game/obj") != "other"
    )
        return errs("�⡭������Ҫ��ɫ��ʯ��һ�ţ�����󲻹��ɡ�\n");
    destruct( bs1 );
    destruct( bs2 );
    destruct( bs3 );
    */
    // ��Ϊ����2�ű�ʯ
    all_mine = all_inventory(me);
    for(i=sizeof(all_mine)-1; i>=0; i-- )
    {
        if( all_mine[i]->id("baoshi")
            && all_mine[i]->query("hj_game/obj") == "other"
        )
        {
            if( !bs1 )
                bs1 = all_mine[i];
            else
            {
                bs2 = all_mine[i];
                break;
            }
        }
    }
    if( !bs1 || !bs2)
        return errs("����Ҫ���ű�ʯ������󲻹��ɡ�\n");
    destruct( bs1 );
    destruct( bs2 );
    // ��ô��OK�
    me->add_temp("hj_score", -score_need );
    me->start_busy(1);
    t = NOR+CYN;
    /*
    message_vision( sprintf(
        CYN"$N%s�ó�һ%s%s%s�ݸ���$n%s��˵�������鷳�㣬��������ĳ� \"%s\" ����\n"
        "$N%s˵�գ����ó���"HIR"��%s��"HIG"��%s��"HIB"��%s�����ű�ʯ�������˵�ʲô��һ��������$n%s��\n"
        "$n%s�ӹ��˽���˵�������ðգ��Ժ��Ҿ���ȥ���㣬���ļ��ɡ���\n"NOR,
            t, sword->query("unit"), sword->query("name"), t, t, type,
            t, t, t, t, t,
            t, t), me, this_object() );
    */
    message_vision( sprintf(
        CYN"$N%s�ó�һ%s%s%s�ݸ���$n%s��˵�������鷳�㣬��������ĳ� \"%s\" ����\n"
        "$N%s˵�գ����ó������ű�ʯ�������˵�ʲô��һ��������$n%s��\n"
        "$n%s�ӹ��˽���˵�������ðգ��Ժ��Ҿ���ȥ���㣬���ļ��ɡ���\n"NOR,
            t, sword->query("unit"), sword->query("name"), t, t, type,
            t, t, t, t, t,
            t, t), me, this_object() );
    destruct(sword);
    set("working", 1);
    remove_call_out( "send_sword" );
    call_out( "send_sword", 5+random(11), me, me->query_temp("this_time_mark"), set );
    // ��΢�ȴ�һ��
    return 1;
}

void send_sword( object me, int me_mark, int set )
{
    object s;
    string t;

    set("working", 0);
    if( !me || !me_ok(me) || !me_mark || me->query_temp("this_time_mark") != me_mark )
        return;
    s = new( __DIR__"hj_obj_weapon" );
    s ->setme( set );
    t = NOR+CYN;

    if( environment(me) == environment(this_object()) )
        message_vision( sprintf(
        CYN"$n%s��һ%s%s%s�ݸ���$N%s��˵��������Ҫ�ĵĽ��Ѿ��ĺ��ˣ���֤���á���\n"NOR,
        t, s->query("unit"), s->query("name"), t, t ), me, this_object() );
    else message_vision( sprintf(
        CYN"ֻ��һλ%s%s�Ҵҵ����˹������ó�һ%s%s%s������$N%s��\n"
        "%s%s˵��������Ҫ�ĵĽ��Ѿ��ĺ��ˣ���֤���á���˵�꣬%s%s�ִҴҵ��뿪�ˡ�\n"NOR,
        query("name"), t, s->query("unit"), s->query("name"),t, t,
        query("name"), t, query("name"), t ), me );

    s->move( me );
}
