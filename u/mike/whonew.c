/// who.c
// Modified by Yu Jue@JY
// Modify by Yu Jue@SJ 1999-06-24
// Modified by Numa@Sj 1999-11-18 ������������ (��׼�����ˣ� bite. 4.23.2000)
// Modified by snowman@SJ 14/11/2000.  ��Ұ���Ϸʱ�����С�
// Modified by Looklove@SJ ���Ӳ鿴���߹�������
inherit F_CLEAN_UP;


mapping party=([
        "emei":         "������",
        "zaixian":      "������Ա",
        "gaibang":      "ؤ��",
        "gumu":         "��Ĺ��",
        "huashan":      "��ɽ��",
        "kunlun":       "������",
        "mingjiao":     "����",
        "murong":       "����Ľ��",
        "quanzhen":     "ȫ���",
        "shaolin":      "������",
        "shenlong":     "������",
        "songshan":     "��ɽ��",
        "taohua":       "�һ���",
        "tianlong":     "������",
        "tiezhang":     "���ư�",
        "wudang":       "�䵱��",
        "xingxiu":      "������",
        "xueshan":      "������",
        "lingjiu":      "���չ�",
        "xiaoyao":      "��ң��",
        "riyue":        "�������",
        "ouyang":       "ŷ������",
]);

int sort_user(object,object);

void create() {
        string *pname = values(party)
        int i = sizeof(pname)

        seteuid(getuid())
        while (i--) partypname = pnamei
}

string opt_party

void remove_busy(object me)
{
        if( me)delete_temp(command_busy, me)
}

mixed main(object me, string arg, int remote)
{
        string str, *option, fname = 
        object *list
        int i, ppl_cnt, cnt, count, wcnt = 0
        int opt_long, opt_id, opt_wiz, opt_wizall, opt_career, opt_zhuanzhan

        if (!remote) {
                if( query_temp(command_busy, me) )
                        return notify_fail(����æ���ء�\n)
set_temp(command_busy, 1,             me)
                call_out(remove_busy, 3, me)
        }


        if( arg ) {
                option -= ({  })
                while( i-- )
                        switch(optioni) {
                                case -l: opt_long = 1
break
                                case -i: opt_id = 1
break
                                case -wizall: opt_wizall = 1
                                case -w: opt_wiz = 1
break
                                case -c: opt_career = 1
break
                                case -z: opt_zhuanzhan = 1
break
                                case -f:
                                case-p:opt_party=query(family/family_name, me)
break
                                default:
                                        if( optioni0=='@' ) {
                                                notify_fail(��·���鲢û�б����롣\n)
                                                if (find_object(DNS_MASTER) && RWHO_Q->send_rwho_q(optioni1..<1,
                                                        me, opt_long & wizardp(me), opt_wiz, opt_party )) {
                                                        // ֻ�й�����Ա������ who @xx -l��Yu Jue@SJ 19990624
                                                        write(����ѶϢ���ͳ������Ժ�\n)
                                                        return 1
                                                return 0
                                        }
                                        if (optioni0 == '-' && !undefinedp(partyoption))
                                        else return notify_fail(ָ���ʽ��who [-l|-i|-w|-p|-c]\n)
                        }
        }
/*
        if (!remote && opt_wizall && find_object(DNS_MASTER)) {
                string *mud = sort_array(keys(DNS_MASTER->query_muds()), -1)
                int m = sizeof(mud)

                while (m--) RWHO_Q->send_rwho_q(mudm, me, 0, 1, opt_party)
        }
*/
        if( opt_long && !remote && !wizardp(me)) {
                if( query(jing, me)<50 )
                        return notify_fail(��ľ���̫���ˣ�û�а취��֪������ҵ���ϸ���ϡ�\n)
                me->receive_damage(jing, 50)
        }

                + ���� + (opt_wiz?������Ա:opt_career?����:opt_zhuanzhan?תվ��Ա:���) + ��\n
        str += repeat_string(��, 40) + \n
        if (opt_party != (null))
                        opt_party :))
        if ( opt_career )
        if ( opt_zhuanzhan && wizardp(me) )

        if( opt_long || opt_wiz ) {
                while( i-- ) {
                        if( remote && wizardp(listi) && query(env/invisibility, listi))continue
                        if (!remote && !me->visible(listi) ) continue
                        if (opt_wiz && !wizardp(listi) ) continue
                        if (interactive(listi)) ppl_cnt++
                        else cnt++
                        if( !wiz_level(listi) && fname != query(family/family_name, listi) )
                        if (!wcnt && wiz_level(listi)) {
                        }
                        str += sprintf(%12s%s%s\n,
                                RANK_D->query_rank(listi),
                                interactive(listi)?
                                        (query_idle(listi) > 120?HIM+NOR: )
                                        :HIG*NOR,
                                listi->short(1)
                        )
                }
        } else {
                string name

                while( i-- ) {
                        // Skip those users in login limbo.
                        if( remote && wizardp(listi) && query(env/invisibility, listi))continue
                        if (!remote && !me->visible(listi)) continue
                        if( !wiz_level(listi) && fname != query(family/family_name, listi)){
                                if (count % (opt_id?4:8)) str += \n
                                str += sprintf(HIY %-*s NOR, opt_id?20:10, (fname?fname:��ͨ����) + ��)
                        }
                        if (!wcnt && wiz_level(listi)) {
                                if (count % (opt_id?4:8)) str += \n
                                str += sprintf(HIY %-*s NOR, opt_id?20:10, ������Ա��)
                        }
                        str += sprintf( %-*s%s,
                                opt_id?19:9,
                                interactive(listi)?
                                        (query_idle(listi) > 120 ? HIM++name+NOR :  +name)
                                        : HIG*+name+NOR,
                                ++count % (opt_id?4:8) ?  : \n
                        )
                        if (interactive(listi)) ppl_cnt++
                        else cnt++
                }
                if( count % (opt_id?4:8) ) str += \n
        }
        str += repeat_string(��, 40) + \n
        str += sprintf(
                "�� %d λ%s�����У�%d λ%s�����У�"HIG"*"NOR" ��ʾ������  "HIM"+"NOR" ��ʾ������\n",
                ppl_cnt, opt_wiz?������Ա:���, cnt, opt_wiz?������Ա:���, query_load_average()
        )

        if( remote ) return str

        me->start_more(str)
        return 1
}

int sort_user(object ob1, object ob2)
{
        string name1, name2
        int l1 = wiz_level(ob1), l2 = wiz_level(ob2)

        if (l1 != l2) return l2 - l1

        if (l1) {

                if (intp(name1)) name1 = 
                if (intp(name2)) name2 = 
                if (name1 > name2) return -1
                if (name1 < name2) return 1
                return 0
        }

        reset_eval_cost()

        if (intp(name1)) name1 = 
        if (intp(name2)) name2 = 
        if (name1 > name2) return -1
        if (name1 < name2) return 1

        if (l1 != l2) return l1 - l2

        // sort by playing time.
        return query(online_total, ob2) - query(online_total, ob1)
        //query(combat_exp, return ob2)-query(combat_exp, ob1)
}

int help(object me)
{
        string *p
        int i,j

        write(@HELP
ָ���ʽ : who 0

���ָ������г����������ϵ���Ҽ���ȼ���

-l ѡ���г��ϳ���ѶϢ��
-i ֻ�г���ҵ�Ӣ�Ĵ��š�
-p ֻ�г�ͬ�ŵ���ҡ�
-f ͬ��
-w ֻ�г��������еĹ�����Ա��
-c ֻ�г����߹���
-Ӣ�Ĵ��� ֻ�г������ɵ���ҡ�

HELP)
        write(sprintf(   %-12s%-12s    %-12s%-12s\n,Ӣ�Ĵ���,������,Ӣ�Ĵ���,������))
        write(----------------------------------------------------------\n
        for (i=0;i<j/2;i++
        
                if (i==(j/2-1)
                
                        write(sprintf(   %-10s��%-12s\n, pi, partyp)
                        continu
                
                if (i/2*2==i
                        write(sprintf(   %-10s��%-12s|, pi, partyp)
                els
                        write(sprintf(   %-10s��%-12s\n, pi, partyp)
        
        write(----------------------------------------------------------\n
        write(@HEL
���ָ� finge
HELP
        return 
