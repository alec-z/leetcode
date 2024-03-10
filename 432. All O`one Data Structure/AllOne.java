import java.util.ArrayList;
import java.util.HashMap;

class AllOne {
    private class Interval {
        public Interval(int b, int e) {
            be = b;
            en = e;
        }

        int be;
        int en;
    }
    private HashMap<String, Integer> strToPos, strToCount;
    private HashMap<Integer, Interval> countToInterval;
    private ArrayList<String> keysList;
    private int size = 0;





    public AllOne() {
        strToPos = new HashMap<>();
        strToCount = new HashMap<>();
        countToInterval = new HashMap<>();
        keysList = new ArrayList<>();
        size = 0;
    }
    
    public void inc(String key) {
        Integer count = strToCount.get(key);
        Integer keyPos = strToPos.get(key);
        Interval toInterval = null, fromInterval = null;
        if (count == null) {
            if (keysList.size() <= size) {
                keysList.add(key);
            } else {
                keysList.set(size, key);
            }
            keyPos = size;
            strToPos.put(key, size);
            size++;
            count = 0;
        } else {
            fromInterval = countToInterval.get(count);
            String tmp = keysList.get(keyPos);
            keysList.set(keyPos, keysList.get(fromInterval.be));
            strToPos.put(keysList.get(fromInterval.be), keyPos);
            keysList.set(fromInterval.be, tmp);
            strToPos.put(tmp, fromInterval.be);

            fromInterval.be = fromInterval.be + 1;
            if (fromInterval.be > fromInterval.en) {
                countToInterval.remove(count);
            } else {
                countToInterval.put(count, fromInterval);
            }
        }
        count++;
        strToCount.put(key, count);

        toInterval = countToInterval.get(count);
        if (toInterval == null) {
            if (fromInterval == null) {
                toInterval = new Interval(size - 1, size - 1);
            } else {
                toInterval = new Interval(fromInterval.be - 1, fromInterval.be - 1);
            }
        } else {
            toInterval.en = toInterval.en + 1;
        }
        countToInterval.put(count, toInterval);
    }
    
    public void dec(String key) {
        Integer count = strToCount.get(key);
        Integer keyPos = strToPos.get(key);
        Interval toInterval = null, fromInterval = null;
        fromInterval = countToInterval.get(count);
        String tmp = keysList.get(keyPos);
        keysList.set(keyPos, keysList.get(fromInterval.en));
        strToPos.put(keysList.get(fromInterval.en), keyPos);
        keysList.set(fromInterval.en, tmp);
        strToPos.put(tmp, fromInterval.en);

        fromInterval.en =  fromInterval.en - 1;
        if (fromInterval.be > fromInterval.en) {
            countToInterval.remove(count);
        } else {
            countToInterval.put(count, fromInterval);
        }
        
        count--;
        if (count == 0) {
            size--;
            strToCount.remove(key);
        } else {
            strToCount.put(key, count);
            toInterval = countToInterval.get(count);
            if (toInterval == null) {
                toInterval = new Interval(fromInterval.en + 1, fromInterval.en + 1);
            } else {
                toInterval.be = toInterval.be - 1;
            }
            countToInterval.put(count, toInterval);
        }
    }
    
    public String getMaxKey() {
        if (size == 0) return "";
        return keysList.get(0);
        
    }
    
    public String getMinKey() {
        if (size == 0) return "";
        return keysList.get(size - 1);
    }

    public static void main(String[] args) {
        AllOne allOne = new AllOne();
        allOne.inc("hello");
        allOne.inc("world");
        allOne.inc("hello");
        allOne.dec("world");
        allOne.inc("hello");
        allOne.inc("leet");
        System.out.println(allOne.getMaxKey());
        allOne.dec("hello");
        allOne.dec("hello");
        allOne.dec("hello");
        System.out.println(allOne.getMaxKey());

        

    }
 }

/**
 * Your AllOne object will be instantiated and called as such:
 * AllOne obj = new AllOne();
 * obj.inc(key);
 * obj.dec(key);
 * String param_3 = obj.getMaxKey();
 * String param_4 = obj.getMinKey();
 */