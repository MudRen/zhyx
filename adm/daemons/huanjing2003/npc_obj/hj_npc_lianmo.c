//                ��׼��������ʾ��                                   |
// �þ����� NPC����ħ��
// by naihe  2003-11-05  ��ï��
// ��ʯ��Ҫ��̫�ߣ����͵� 05-9-1 14:43

#include <ansi.h>
#include <errs_func.h>
// �����и� errs() ���� notify_fail() ���� write(msg), return 1;
inherit NPC;

#include "hj_settings/room_amount_hj.h"
#define        MY_ROOM_MARK        HJ_ROOM_AMOUNT-9
        // ��NPC�������� HJ �������Ϸ����䴦����Ч
#include "zj_lm_tarder_prefunc.h"

#define        SXF            20
        // �۸񣬼�������

void create()
{
    set_name( "��ħ��", ({ "lianmo jiang", "jiang" }) );
    set("nickname", HIM"���绽�� ��������"NOR );

    set("long", "����һλħ��ǿ�����ħ����ר�Ӹ������ħ��ˮ�������⡣
=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
  ��ĳħ��ˮ���ĳ� "HIW"���ˮ��"NOR"�� <lm kfsj ˮ����ID>
  ��ĳħ��ˮ���ĳ� "MAG"����ˮ��"NOR"�� <lm bysj ˮ����ID>
  ��ĳħ��ˮ���ĳ� "HIC"����ˮ��"NOR"�� <lm llsj ˮ����ID>
  ��ĳħ��ˮ���ĳ� "HIG"����ˮ��"NOR"�� <lm ydsj ˮ����ID>
  ��ĳħ��ˮ���ĳ� "YEL"��ʯˮ��"NOR"�� <lm gssj ˮ����ID>
  ��ĳħ��ˮ���ĳ� "RED"�ɻ�ˮ��"NOR"�� <lm fhsj ˮ����ID>
  ��ĳħ��ˮ���ĳ� "BLU"���ˮ��"NOR"�� <lm dhsj ˮ����ID>
�����ⱦʯ 2 �ţ����þ��÷� "+SXF+" �� / �Ρ�

�޲�ĳħ��ˮ������֮ʹ�ô����ָ�����<lm up ˮ����ID>
�����ⱦʯ 1 �ţ��þ��÷� "+(SXF/2)+" �� / �Ρ�
=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
    set("gender","Ů��");
    set("age",91);
    set("per",11);
    set("attitude","friendly");
    set("no_refresh",1);
    set("hj_game/npc","lianmo");

    setup();
}

void init()
{
    add_action("do_lianmo", ({ "lianmo", "lm" }) );
}

// �ú������� zhujian shi �ģ�һЩ���������ø���
// �������������� #include ���������ɡ�
int do_lianmo( string arg )
{
    object me = this_player(), bs1, bs2, bs3, *all_mine, sword;
    string sword_id, type, *list, t;
    int i, set, score_need;

    if( !ob_ok() || !me_ok(me) ) return 0;
    if( me->is_busy() || me->query_temp("hj_need_waiting") )
        return errs("�㻹æ���ء�\n");

    if( !arg || sscanf( arg, "%s %s", type, sword_id ) != 2 )
        return errs("����������ħ��ˮ����(look lianmo jiang)��\n");

    if( query("working") )
        return errs("���⻹�е㹤��û��ɣ����Ե�һ����ɡ�\n");

    list = ({ "kfsj","bysj","llsj","ydsj","gssj","fhsj","dhsj" });
    // �����˳��� hj_obj_weapon.c ���˳����һ���ġ�

    set = member_array( type, list );
    if( set == -1 && type != "up" )
        return errs("�ȡ��� \""+type+"\" ����ħ��ˮ�����ҿ�������û����������\n");

    set += 9;
    // ��� hj_obj_weapon.c �����á�

    sword = present( sword_id, me );
    if( !sword ) return errs("���û����������ˮ��������Ϊ�����Ǹ�ʲô�κΰ�������ƾ�ձ���㣿\n");
    if( sword->query("hj_game/obj") != "magic" )
        return errs( sword->query("name")+"���ǿ���������ħ��ˮ����\n");
    // �������������ˮ��������������Ҳ����ʶ

    score_need = (type == "up" ? SXF/2 : SXF);
    if( me->query_temp("hj_score") < score_need +1 )
        return errs("�����޷��ģ���α�ʾ��ĳ���ѽ��\n");
    // ok. up it.
    if( type == "up" )
    {
        if( sword->query("use_times") >= sword->query("real_use_times") )
            return errs("��ˮ���ﻹ������ħ�������ǲ��������˰ɡ�\n");

        all_mine = all_inventory(me);
        // ������Ͽ϶���sj�����ؽ��� !all_mine ���ж�
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
            CYN"$N%s�ó�һ%s%s%s�ݸ���$n%s��˵�������鷳�����������ˮ������\n"
            "$N%s˵�գ����ó���һ�ű�ʯ�������˵�ʲô��һ��������$n%s��\n"
            "ֻ��$n%s�ӹ���ˮ������������ֻŪ�˼��£��Ͱ����ݸ���$N%s��\n"
            "$n%s˵��������������ˮ���Ѿ��޺��ˣ���֤���á���\n"NOR,
                t, sword->query("unit"), sword->query("name"), t, t,
                t, t,
                t, t,
                t), me, this_object() );
        return 1;
    }

    // ��ô���ǻ�sj�
    // ̫�õĲ���(ʹ���˺ܶ�ε�)
    if( sword->query("use_times") < sword->query("real_use_times")/2 )
        return errs("��ˮ���������Ѿ�˥�ܣ��㻹����������ɡ�\n");
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
        "$n%s�ӹ���ˮ����˵�������ðգ��Ժ��Ҿ���ȥ���㣬���ĺ���������\n"NOR,
            t, sword->query("unit"), sword->query("name"), t, t, type,
            t, t, t, t, t,
            t, t), me, this_object() );
    */
    message_vision( sprintf(
        CYN"$N%s�ó�һ%s%s%s�ݸ���$n%s��˵�������鷳�㣬��������ĳ� \"%s\" ����\n"
        "$N%s˵�գ����ó������ű�ʯ�������˵�ʲô��һ��������$n%s��\n"
        "$n%s�ӹ���ˮ����˵�������ðգ��Ժ��Ҿ���ȥ���㣬���ĺ���������\n"NOR,
            t, sword->query("unit"), sword->query("name"), t, t, type,
            t, t, t, t, t,
            t, t), me, this_object() );

    destruct(sword);
    set("working", 1);
    remove_call_out( "send_sj" );
    call_out( "send_sj", 5 + random(11), me, me->query_temp("this_time_mark"), set );
    // ��΢�ȴ�һ��

    return 1;
}

void send_sj( object me, int me_mark, int set )
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
        CYN"$n%s��һ%s%s%s�ݸ���$N%s��˵��������Ҫ�ĵ�ˮ���Ѿ��ĺ��ˣ���ȥ�ðɡ���\n"NOR,
        t, s->query("unit"), s->query("name"), t, t ), me, this_object() );
    else message_vision( sprintf(
        CYN"ֻ��һλ%s%s�Ҵҵ����˹������ó�һ%s%s%s������$N%s��\n"
        "%s%s˵��������Ҫ�ĵ�ˮ���Ѿ��ĺ��ˣ���ȥ�ðɡ���˵�꣬%s%s�ִҴҵ��뿪�ˡ�\n"NOR,
        query("name"), t, s->query("unit"), s->query("name"),t, t,
        query("name"), t, query("name"), t ), me );

    s->move( me );
}
