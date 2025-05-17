#ifndef GROUNDWATERDIALOG_H
#define GROUNDWATERDIALOG_H

#include <QDialog>
#include "groundwaterdialogmodel.h"

QT_BEGIN_NAMESPACE
class QGroupBox;
class QLabel;
class QCheckBox;
class QRadioButton;
class QLineEdit;
class QDialogButtonBox;
QT_END_NAMESPACE

class GroundwaterDialog : public QDialog
{
    Q_OBJECT

public:
    GroundwaterDialog(bool isMSE, const GroundwaterDialogModel& initialData, QWidget* parent = nullptr);
    ~GroundwaterDialog();

    GroundwaterDialogModel getDialogData() const { return m_currentData; }

private slots:
    void enableWaterTableGroupWidgets(bool checked);
    void updateElevationBuddyLabel(const QString& text);
    void applyToAllSectionsHolderFunction(bool checked);

private:
    bool m_isMSE;
    GroundwaterDialogModel m_currentData;

    QCheckBox* m_includeWaterTableCheckbox;
    QGroupBox* m_waterTableGroupBox;

    QRadioButton* m_constantRadioButton;
    QLabel* m_waterElevationLabel;
    QLineEdit* m_waterElevationLineEdit;

    QRadioButton* m_differentialRadioButton;
    QLabel* m_backslopeWaterElevationLabel;
    QLineEdit* m_backslopeWaterElevationLineEdit;
    QLabel* m_frontFaceWaterElevationLabel;
    QLineEdit* m_frontFaceWaterElevationLineEdit;

    QCheckBox* m_infiltratesReinforcedZoneCheckbox;
    QCheckBox* m_applyToAllSectionsCheckbox;

    QDialogButtonBox* m_okCancelButtonBox;

    void virtual accept() override;
    void virtual reject() override { QDialog::reject(); };

    void setupUi(bool isMSE);
    void loadUiData(const GroundwaterDialogModel& data);
    void saveUiData();
};

#endif // GROUNDWATERDIALOG_H
