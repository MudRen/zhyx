// ���ϵͳ
// ��ԭ���������Ӱ���������֣����޸��˴洢�ṹ
// Updated By Yuchang@zhyx

#include <ansi.h>

// #pragma optimize
// #pragma save_binary

inherit F_SAVE;
inherit F_DBASE;

// ������������10��
#define MAX_PARTY_FAME         1000000000

// ÿ����������100������
#define MAX_HATRED_PERSON       100

// �����˳�����ʱ��ÿ���Ƴ����ٸ�
#define HATREDP_REMOVED         10

mapping party_fame;
mapping last_party_fame;

private int sort_hatred(string, string, mapping);

public string query_save_file() { return DATA_DIR "bangd"; }

void create()
{
        seteuid(getuid());
        restore();
        set_heart_beat(7200 + random(3600));
        if (! mapp(party_fame)) party_fame = ([ ]);
}

void remove() { save(); }

public void mud_shutdown()  { save(); }

public void reset_party()
{
        string *all_fam;
        string fam;

        all_fam = keys(party_fame) - ({ 0 });

        foreach (fam in all_fam)
        {
		last_party_fame[fam] += party_fame[fam];
		party_fame[fam] = 0;
	}
        save();
        return;
}

public string max_party(int max_sw)
{
        string *all_fam;
        string fam, max_fam;

        all_fam = keys(party_fame) - ({ 0 });
	if (sizeof(all_fam) < 2)   return 0;

        foreach (fam in all_fam)
        {
		if (party_fame[fam] > max_sw)
                {
                   	max_sw = party_fame[fam];
                      	max_fam = fam;
	        }
	}
        return max_fam;
}

private void heart_beat()
{
	string party_name;

	party_name = max_party(1000);
	if (!stringp(party_name))   return;
        CHANNEL_D->do_channel(this_object(), "rumor", "��˵��" +
        	party_name + "��������ʢ���ѳ�Ϊ���������İ�ᡣ");
	save();
}

// ���ذ���������������Ϊ�գ�����mapping���ͣ����������а�
// ��������������������� �򷵻ظ��������ڵ��Ǹ�������
// ������������ǰ�ᣬ�򷵻ظð���������
public mixed query_party_fame(mixed ob)
{
        string fname;

        if (stringp(ob))
                return party_fame[ob];

        if (objectp(ob))
        {
                if (stringp(fname = ob->query("party/party_name")))
                        return party_fame[fname];
                else
                        return 0;
        }

        return party_fame;
}

// ��ѯ����İ��������Ϣ
public mapping query_all_last_party_fame()
{
        if (! mapp(last_party_fame))
                // û���������Ϣ�����ؽ����
                return party_fame;

        // ��������İ��������Ϣ
        return last_party_fame;
}

// ��ѯ���ĳ����Ϣ�������ob�����ǰ������֣�Ҳ���ǰ��
// �е����
public mapping query_party_hatred(mixed ob)
{
        mapping hatred;
        string fname;

        if (objectp(ob))
                fname = ob->query("party/party_name");
        else
        if (stringp(ob))
                fname = ob;
        else
                fname = 0;

        if (! stringp(fname) || ! mapp(hatred = query(fname + "/hatred")))
                return 0;

        return hatred;
}

// �仯��������������ob�����ǰ������֣�Ҳ���ǰ���е���
// �
public void add_party_fame(mixed ob, int n)
{
        int new_fame;
        string fname;

        if (objectp(ob))
                fname = ob->query("party/party_name");
        else
        if (stringp(ob))
                fname = ob;
        else
                fname = 0;

        if (! stringp(fname) || undefinedp(query(fname + "/member")))
                return;

        // �����µİ������
        new_fame = party_fame[fname] + n;
        if (new_fame > MAX_PARTY_FAME)
                new_fame = MAX_PARTY_FAME;
        party_fame[fname] = new_fame;
        save();
        return;
}

// �����ɱ
public void party_kill(object killer, object victim)
{
        int kexp;
        int vexp;
        string vfam;
        string kfam;
        string kid;
        int fame_delta;
        mapping hatred;
        mixed *d;

        // ֻ�����֮��ĳ�ɱ�ż�������
        if (! objectp(killer) || ! playerp(killer) ||
            ! objectp(victim) || ! playerp(victim))
                return;

        // ��ʦ֮��ıȻ��ɲ�������
        if (wizardp(killer) || wizardp(victim))
                return;

        // �鿴��������������İ��
        kfam = killer->query("party/party_name");
        vfam = victim->query("party/party_name");

        if (killer->is_brother(victim) && killer->is_killing(victim->query("id")))
                // ɱ������ֵܣ���������10%
                killer->add("weiwang", -killer->query("weiwang") / 10);

        if (! stringp(kfam) && ! stringp(vfam))
                // �����ڰ���ڣ����ؼ�����
                return;

        kexp = killer->query("combat_exp");
        vexp = victim->query("combat_exp");

        if (kfam == vfam)
        {
                if (! killer->is_killing(victim->query("id")))
                        // ʧ����ɱ���������
                        return;

                // �ֵܼ��ɱ��������ᣬֱ�ӿ۳����͸���1/10������
                add_party_fame(kfam, -party_fame[kfam] / 10);
                killer->add("weiwang", -killer->query("weiwang") / 10);
                return;
        }

        if (kexp > vexp * 2 && vexp >= 100000)
        {
                // ɱ�ֵľ���Զ���ڶԷ�����ǿ�������������ұ�ɱ��
                // ����һ���ľ��飬�⽫���°�������Ľ��͡�
                fame_delta = 100 - (vexp / 10000);
                if (fame_delta < 10)   fame_delta = 10;
                fame_delta = -fame_delta;
        } else
                // ˫����಻�Ǻܴ�����ɱ�����ڰ������
                fame_delta = 5 + random(5);

        // �鿴ɱ�����ڵİ���Ƿ������ߣ������ޣ����ܹ�
        // ���������ı仯��
        if (stringp(kfam))
        {
                string path;
                int wang;

                path = kfam + "/hatred/"+ victim->query("id");
                d = query(path);
                if (arrayp(d) && sizeof(d) >= 2 && intp(d[1]))
                {
                        // ������ߣ�����ö��������
                        if (d[1] > 2000)
                                CHANNEL_D->do_channel(this_object(), "rumor",
                                        "��˵" + killer->name(1) + "������" +
                                        victim->name(1) + "��Ϊ" +
                                        kfam + "����һ�ڶ�����");
                        wang = d[1] / 20;
                        if (wang < 5)     wang = 5;
                        if (wang > 50)    wang = 50;
                        fame_delta += wang;
                        wang = d[1] / 3;

                        // �Դ��˵ĳ�޽���(���͵�Ҫ�����ӵ�Ҫ��)��
                        // ������Կ�fame_delta ���޶ȹ�ʽ�Ĳ���
                        d[1] -= wang;
                        if (d[1] <= 0)
                                delete(path);
                        else
                                set(path, d);
                }
        }

        // ����������������
        add_party_fame(killer,  fame_delta);
        add_party_fame(victim, -fame_delta);

        // ͳ�Ƹ�ɱ�ֶԱ��ŵĲк��̶�
        if (! stringp(vfam))
                return;

        // ��޳̶Ⱥ������ı仯������һ����������(K����)����
        // �ǳ�޳̶ȵ��������ı仯��
        vexp = vexp / 1000 + 1;
        if (vexp > 5000)
                vexp = (vexp - 5000) / 16 + 2000;
        else
        if (vexp > 1000)
                vexp = (vexp - 1000) / 4 + 1000;

        kid = killer->query("id");
        if (! mapp(hatred = query(vfam + "/hatred")))
        {
                set(vfam + "/hatred/" + kid,
                    ({ killer->name(), vexp }));
                return;
        }

        // ÿ���������¼���ɸ�����
        if (! undefinedp(d = hatred[kid]))
        {
                if (! arrayp(d) || sizeof(d) < 2 ||
                    ! intp(d[1]) || ! stringp(d[0]))
                {
                        // ���ID�����ݳ��˹���
                        d = 0;
                }
        } else
        if (sizeof(hatred) >= MAX_HATRED_PERSON)
        {
                string *ids;
                int i;

                // ����ȥ��һЩ�ˣ�Ϊʲô��ȥ��һ��������Ϊ
                // �˷�ֹ����Ƶ���Ľ��й��˲�����
                ids = sort_array(keys(hatred),
                                 (: sort_hatred :), hatred);
                for (i = 0; i < sizeof(ids) && i < HATREDP_REMOVED; i++)
                        map_delete(hatred, ids[i]);
        }

        if (! arrayp(d))
                d = ({ killer->name(1), vexp });
        else
        {
                d[0] = killer->name(1);
                d[1] += vexp;
        }

        // ��¼����˵���Ϣ
        hatred[kid] = d;
        return;
}

// ȥ�����а���ĳ���˵ĳ����Ϣ
public void remove_hatred(string id)
{
        mapping dbase, party, hatred;
        string fam;

        if (! mapp(dbase = query_entire_dbase()))
                // ���ڻ�û�г����Ϣ
                return;

        // �������еİ��
        foreach (fam in keys(dbase))
        {
                reset_eval_cost();

                if (! mapp(party = dbase[fam]))
                        continue;

                if (mapp(hatred = party["hatred"]))
                        // ȥ���ð���ĳ�˵ĳ����Ϣ
                        map_delete(hatred, id);

                if (! mapp(hatred) || sizeof(hatred) < 1)
                        // �������Ѿ�û�г����Ϣ
                        map_delete(party, "hatred");
        }
        save();
        return;
}

// �������
public void create_party(string fname, int base, object *obs)
{
        string *info;
	mapping players;
        int i;

        party_fame[fname] = base;
        if (! mapp(last_party_fame))
                last_party_fame = ([ fname : base ]);
        else
                last_party_fame[fname] = base;

	players = ([]);
	for (i=0; i<sizeof(obs); i++)
	{
		info = ({ obs[i]->query("party/right"), obs[i]->query("name"), 0 });
		players += ([ obs[i]->query("id") : info ]);

	}
        set(fname, ([ "member" : players,
        	      "money"  : 0,
                      "time"   : time() ]));

        save();
        CHANNEL_D->do_channel(this_object(), "rumor",
                   "��˵��Ұ�᡺" + fname + "���ڽ����г����ˡ�");
        return;

}

// ��ɢ���
public void dismiss_party(string fname)
{
        string *ids;
        string id;

        // �������е�������ҵ������Ϣ
        if (mapp(query(fname + "/member")))
	        ids = keys(query(fname + "/member"));

        if (arrayp(ids))
        {
                // ����л�����ң�������ǵ���Ϣ
                foreach (id in ids)
                {
                	reset_eval_cost();
                	UPDATE_D->clear_user_data(id, "party");
                	UPDATE_D->clear_user_data(id, "room");
                }
        }

        // ���������Ϣ
        map_delete(party_fame, fname);
        if (mapp(last_party_fame)) map_delete(last_party_fame, fname);

        // �������������Ϣ
        rm(BANG_DIR + fname);
        delete(fname);
        save();
        CHANNEL_D->do_channel(this_object(), "rumor",
                   "��˵" + fname + "�˲ŵ��㣬���պ��Ѿ���ɢȥ���Ӵ˽������޴��ֺ��ˡ�");
	return;
}

// ��ѯ����еĵ���
public mapping query_members(mixed ob)
{
        mapping member;
        string fname;

        if (objectp(ob))
                fname = ob->query("party/party_name");
        else
        if (stringp(ob))
                fname = ob;
        else
                fname = 0;

        if (! stringp(fname) || ! mapp(member = query(fname + "/member")))
                return 0;

        return member;
}

// �Ӱ����ȥ��һ����
public varargs void remove_member_from_party(mixed fname, string id)
{
        mapping party, member;

        if (objectp(fname))
        {
                // fname is user object
                id = fname->query("id");
                if (! stringp(fname = fname->query("party/party_name")))
                        return;
        } else
        if (! stringp(fname))
                // or fname must be a league name
                return;

        if (! mapp(party = query(fname)) ||
            ! mapp(member = party["member"]))
                // no such party or no member in the party
                return;

	map_delete(member, id);
	set(fname + "/member", member);
        add_party_fame(fname, -1);
	save();
        if (sizeof(keys(member)) < 2)
		dismiss_party(fname);

        return;
}

// �ڰ��������һ����
public void add_member_into_party(string fname, string id, string cname)
{
        mapping member;
	string *info;
	object player;

        if (! mapp(member = query(fname + "/member")))
                return 0;

        if (member_array(id, keys(member)) != -1)
                return 0;

	info = ({ 5, cname, 0 });
        member += ([ id : info ]);
        set(fname + "/member", member);

        // �����ID���ߣ���EXP>200K������1������
        if (userp(player = find_player(id)) && player->query("combat_exp") > 200000)
	        add_party_fame(fname, 1);
	return;
}

// �޸İ���ԱȨ��
public void modify_member_auth(string fname, string id, int auth)
{
        mapping member;

        if (! mapp(member = query(fname + "/member")))
                return 0;

        if (member_array(id, keys(member)) == -1)
                return 0;

        member[id][0] = auth;
        set(fname + "/member", member);
	save();
	return;
}

// ��������
private int sort_hatred(string id1, string id2, mapping hatred)
{
        mixed *d1, *d2;

        if (! arrayp(d1 = hatred[id1]) || sizeof(d1) < 2 || ! intp(d1[1]))
                return -1;

        if (! arrayp(d2 = hatred[id2]) || sizeof(d2) < 2 || ! intp(d2[1]))
                return 1;

        return d1[1] - d2[1];
}

// ��¼�����־�ļ�
public int party_save_record(string fname, string str)
{
	fname = BANG_DIR + fname;
	if(!write_file(fname,str))
		return 0;
	else	return 1;
}

// ������
public void cun_money_to_party(object ob, int amount)
{
	string id, fname;
	mapping party;

	if (! objectp(ob))
		return;

	if (! stringp(fname = ob->query("party/party_name")))
		return;

	id = ob->query("id");
	if (! mapp(party = query(fname)))
                return;

	party["member"][id][2] += amount;
	party["money"] += amount;
	set(fname, party);
	save();
	return;
}

// ��ѯ���������
public int check_party_money(string fname)
{
	return query(fname + "/money");
}

// �Ӱ��ȡ��
public void qu_money_from_party(object ob, int amount)
{
	string id, fname;
	mapping party;

	if (! objectp(ob))
		return;

	if (! stringp(fname = ob->query("party/party_name")))
		return;

	id = ob->query("id");
	if (! mapp(party = query(fname)))
                return;

	party["money"] -= amount;
	set(fname, party);
	save();
	return;
}
