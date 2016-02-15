
import java.util.TreeMap;

public class MemoryManager
{
    TreeMap<Integer, Area> free;
    TreeMap<Integer, Area> used;

    public MemoryManager(int size)
    {

        free = new TreeMap<Integer, Area>();
        used = new TreeMap<Integer, Area>();
        free.put(0, new Area(0, size));
    }

    public Area aquire(int amount) {

        Area a = null;
        synchronized (free) {

            for (int i : free.keySet()) {

                if (free.get(i).getSize() > amount) {

                    used.put(i, new Area(i, i + amount));
                    free.put(i + amount, new Area(i + amount, free.get(i).getEnd()));
                    free.remove(i);
                    a = new Area(i, i + amount);
                    break;

                }

            }

        }
        return a;
    }

    public void release(int handle) {

        int prevKey = handle;
        boolean triggered = false;

        synchronized (free) {

            for (int i : free.keySet()) {

                if (free.get(i).getEnd() == handle) {

                    free.put(i, new Area(i, used.get(handle).getEnd()));
                    prevKey = i;
                    triggered = true;

                } else if (used.get(handle).getEnd() == free.get(i).getStart()) {

                    free.put(prevKey, new Area(prevKey, free.get(i).getEnd()));
                    free.remove(i);
                    triggered = true;
                    break;

                }

            }

            if (triggered == false) {

                free.put(handle, new Area(handle, used.get(handle).getEnd()));

            }

        }

        synchronized (used) {

            used.remove(handle);

        }

    }

    public void print()
    {
        synchronized (free)
        {
            System.out.println("\nFree");
            free.forEach((k, v) -> System.out.println(k + "->" + v.getEnd() + "(" + v.getSize() + ")"));
            System.out.println("Used");
            used.forEach((k, v) -> System.out.println(k + "->" + v.getEnd() + "(" + v.getSize() + ")"));
        }
    }

    public Area getFirstFree()
    {
        return free.firstEntry().getValue();
    }

}