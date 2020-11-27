// enable.c
// edit by smallfish

#include <ansi.h>
#include <getconfig.h>

inherit F_CLEAN_UP;

string *valid_types = ({
        "force",
        "dodge",
        "unarmed",
        "cuff",
        "strike",
        "finger",
        "hand",
        "claw",
        "sword",
        "blade",
        "staff",
	"hammer",
        "club",
        "whip",
        "dagger",
        "throwing",
        "parry",
        "magic",
	"medical",
        "poison",
        "chuixiao-jifa",
        "tanqin-jifa",
        "guzheng-jifa",
	"cooking",
});

int main(object me, string arg)
{
        string file,dir,filename;
        string msg,msg1;
        int i, j, l, is_force;
        mixed *all_file;

        seteuid(getuid());

        if (! arg)
                return notify_fail("ָ���ʽ��checkskill <skill>\n");

        if (! stringp(file = SKILL_D(arg)) || file_size(file + ".c") <= 0)
                return notify_fail(LOCAL_MUD_NAME() + "��û��"+arg+"�����书��\n");

        msg = HIW + "��ѯ�书��" + NOR + HIY + arg + "\n" + NOR;
        msg += HIC"--------------------------------------------------\n"NOR;

        msg += HIW + "�书�������֣�" + NOR + HIY + to_chinese(arg) + "\n" + NOR;
        is_force = 0;
        if (SKILL_D(arg)->valid_enable("force"))
        {
                is_force = 1;
                msg += HIR"���书��һ�ָ߼��ڹ���\n"NOR;
        }
        msg += HIC"--------------------------------------------------\n"NOR;

        if (member_array(arg,valid_types) != -1)
        {
                msg += HIW"����һ�ֻ����书��\n"NOR;
                write(msg);
                return 1;
        }

        msg += HIW "���书������������Ϊ��\n" NOR;

        msg1 = "";
        j = 0;
        for (i = 0;i < sizeof(valid_types);i++)
        {
                if (SKILL_D(arg)->valid_enable(valid_types[i]))
                {
                        j++;
                        msg1 += sprintf(HIY"%-20s%s"NOR,
                                       valid_types[i],
                                       (j%3) ? " " : "\n"
                                      );
                }
        }
        if (msg1 == "") 
                msg1 = HIR"�ޡ�\n"NOR;
        else
                msg1 += "\n";
        msg += msg1;
        msg += HIC"--------------------------------------------------\n"NOR;

        msg1 = "";
        j = 0;
        msg += HIW "���书�����о��У�\n" NOR;
        dir = file;

        if (dir[strlen(dir) - 1] != '/')
                dir += "/";

        if (is_force)
                dir += "perform/";

        if (file_size(dir) != -2)
                msg1 += HIR"�ޡ�\n"NOR;
        else
        {
                all_file = get_dir(dir);
                if (!sizeof(all_file))
                        msg1 += HIR"�ޡ�\n"NOR;
                else
                {
                        for (i = 0;i < sizeof(all_file);i++)
                        {
                                filename = all_file[i];
                                l = strlen(filename);
                                if (filename[l - 1] == 'c' && filename[l - 2] == '.')
                                {
                                        j++;
                                        msg1 += sprintf(HIY"%-20s%s"NOR,
                                                        filename[0..l-3],
                                                        (j%3) ? " " : "\n"
                                                       );
                                }
                        }
                        if (msg1 == "") 
                                msg1 = HIR"�ޡ�\n"NOR;
                        else
                                msg1 += "\n";
                }
        }
        msg += msg1;
        if (!is_force)
        {
                write(msg);
                return 1;
        }
        msg += HIC"--------------------------------------------------\n"NOR;

        msg1 = "";
        j = 0;
        msg += HIW "���ڹ����������⹦�ܣ�\n" NOR;

        dir = file;

        if (dir[strlen(dir) - 1] != '/')
                dir += "/";
 
        if (file_size(dir+"exert/") == -2)
                all_file = get_dir(dir+"exert/");
        else if (file_size(dir) == -2)
                all_file = get_dir(dir);
        else 
        {
                msg += HIR"�ޡ�\n"NOR;
                write(msg);
                return 1;
        }

        if (!sizeof(all_file))
        {
                msg += HIR"�ޡ�\n"NOR;
                write(msg);
                return 1;
        }

        for (i = 0;i < sizeof(all_file);i++)
        {
                filename = all_file[i];
                l = strlen(filename);
                if (filename[l - 1] == 'c' && filename[l - 2] == '.')
                {
                        j++;
                        msg1 += sprintf(HIY"%-20s%s"NOR,
                                        filename[0..l-3],
                                        (j%3) ? " " : "\n"
                                       );
                }
        }          
        if (msg1 == "") 
                msg1 = HIR"�ޡ�\n"NOR;
        else
                msg1 += "\n";
        msg += msg1;
        write(msg);
        return 1;
}
int help(object me)
{
        write(@HELP
ָ���ʽ : checkskill <��������>

���ָ��������ָ����ĳ�ּ��ܣ���ʾ�ü��ܵľ��У����⹦�ܵȵȡ�

HELP );
        return 1;
}