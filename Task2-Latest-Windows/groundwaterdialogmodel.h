#ifndef GROUNDWATERDIALOGMODEL_H
#define GROUNDWATERDIALOGMODEL_H
#include <QString>

struct GroundwaterDialogModel {
    bool includeWaterCheck = false;

    bool constantRadioCheck = true;
    QString waterElevationLabelText = "Water elevation (ft):";
    QString waterElevationValue = "0";

    bool differentialRadioCheck = !constantRadioCheck;
    QString backslopeWaterElevationLabelText = "Backslope water elevation (ft):";
    QString backslopeWaterElevationValue = "0";
    QString frontFaceWaterElevationLabelText = "Front face water elevation (ft):";
    QString frontFaceWaterElevationValue = "0";

    bool infiltratesReinforcedZoneCheck = false;
    bool applyToAllSectionsCheck = false;
};

#endif // GROUNDWATERDIALOGMODEL_H
