import java.util.ArrayList;
import java.util.HashMap;

class LFUCache {
    private class Interval {
        public Interval(int b, int e) {
            be = b;
            en = e;
        }

        int be;
        int en;
    }
    private class Pair {
        public Pair(Integer key, Integer value) {
            this.key = key;
            this.value = value;
        }
        Integer key;
        Integer value;

    }
    private HashMap<Integer, Integer> keyToPos, keyToCount;
    private HashMap<Integer, Interval> countToInterval;
    private ArrayList<Pair> cache;
    private int size = 0;
    private int capacity;





    public LFUCache(int capacity) {
        this.capacity = capacity;
        keyToPos = new HashMap<>();
        keyToCount = new HashMap<>();
        countToInterval = new HashMap<>();
        cache = new ArrayList<>();
        size = 0;
    }
    
    public void inc(Integer key, Integer value) {
        Integer count = keyToCount.get(key);
        Integer keyPos = keyToPos.get(key);
        Interval toInterval = null, fromInterval = null;
        Pair pair = new Pair(key, value);
        if (count == null) {
            if (cache.size() <= size) {
                cache.add(pair);
            } else {
                cache.set(size, pair);
            }
            keyPos = size;
            keyToPos.put(key, size);
            size++;
            count = 0;
        } else {
            fromInterval = countToInterval.get(count);
            Pair tmp = cache.get(keyPos);
            if (pair.value != null) {
                tmp.value = pair.value;
            }
            cache.set(keyPos, cache.get(fromInterval.be));
            keyToPos.put(cache.get(fromInterval.be).key, keyPos);
            cache.set(fromInterval.be, tmp);
            keyToPos.put(tmp.key, fromInterval.be);

            fromInterval.be = fromInterval.be + 1;
            if (fromInterval.be > fromInterval.en) {
                countToInterval.remove(count);
            } else {
                countToInterval.put(count, fromInterval);
            }
        }
        count++;
        keyToCount.put(key, count);

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

        keyPos = toInterval.en;
    }
    public int get(int key) {
        Integer pos = keyToPos.get(key);
        Integer res;
        if (pos == null) {
            return -1;   
        } else {
            res = cache.get(pos).value;
        }
        inc(key, null);
        return res;
    }

    public void put(int key, int value) {
        Integer pos = keyToPos.get(key);
        if (pos == null) {
            if (size < capacity) {
                inc(key, value);
            } else {
                Pair last_pair = cache.get(size - 1);
                Integer count = keyToCount.get(last_pair.key);
                Interval fromInterval = countToInterval.get(count);
                fromInterval.en =  fromInterval.en - 1;
                if (fromInterval.be > fromInterval.en) {
                    countToInterval.remove(count);
                } else {
                    countToInterval.put(count, fromInterval);
                }
                keyToCount.remove(last_pair.key);
                keyToPos.remove(last_pair.key);
                size--;
                inc(key, value);
            }
            //insert; 
        } else {
            inc(key, value);
        }
    }

    public static void main(String[] args) {
        LFUCache l = new LFUCache(2);
        l.put(1, 1);
        l.put(2, 2);
        l.get(1);
        l.put(3, 3);
        l.get(2);
        System.out.println(l.get(2));
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