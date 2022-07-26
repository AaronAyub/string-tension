#include <vector>
#include "stringweight.h"
#include "stringtype.h"
#include <cstdlib>
namespace strlib {
    extern const std::vector<strlib::StringWeight> stringsPL;
    extern const std::vector<strlib::StringWeight> stringsNW;
    extern const std::vector<strlib::StringWeight> stringsXLB;
    
    double getUnitWeight(double gauge, StringType type) {
        // Prevent the user from entering invalid gauges
        if (gauge <= 0) {
            return 0;
        }

        // Pick the list of strings to estimate weight from
        std::vector<StringWeight> list;
        switch (type) {
            case PL:
                list = stringsPL;
                break;
            case NW:
                list = stringsNW;
                break;
            case XLB:
                list = stringsXLB;
                break;
        }

        // If the gauge is smaller than any reference string on the list
        if (gauge < list[0].gauge) {
            return estimateWeight(gauge, list[0], list[1]);
        }
        // If the gauge >= the lowest reference gauge, but less than the largest reference string
        for (int i = 0; i < list.size() - 1; ++i) {
            if (gauge == list[i].gauge) return list[i].unitWeight;
            else if (gauge < list[i+1].gauge) return estimateWeight(gauge, list[i], list[i+1]);
        }
        
        // If the gauge is equal to the largest reference string
        if (gauge == list.back().gauge) return list.back().unitWeight;
        // Otherwise, the gauge is larger than the largest reference string on the list
        else return estimateWeight(gauge, list[list.size() - 2], list.back());
    }

    double estimateWeight(double gauge, const StringWeight& low, const StringWeight& high) {
        // Calculate the ratio of gauge/unit weight between the two reference strings.
        double refGaugeDifference = high.gauge - low.gauge;
        double refWeightDifference = high.unitWeight - low.unitWeight;
        double ratio = refWeightDifference / refGaugeDifference;

        // If the input gauge is closer to the larger reference string, use that for the estimate
        if (std::abs(gauge - high.gauge) < std::abs(gauge - low.gauge)) {
            double gaugeDifference = gauge - high.gauge;
            return high.unitWeight + (gaugeDifference * ratio);
        }
        // Otherwise, use the smaller string for the estimate
        else {
            double gaugeDifference = gauge - low.gauge;
            return low.unitWeight + (gaugeDifference * ratio);
        }
    }
}

