import Sequelize, { Model } from 'sequelize';

class Measurement extends Model {
  static init(sequelize) {
    super.init(
      {
        sensor_id: Sequelize.STRING,
        word: Sequelize.INTEGER,
        value: Sequelize.STRING,
      },
      {
        sequelize,
        tableName: 'measurements',
      }
    );

    return this;
  }

  static associate(model) {
    this.hasMany(model.Sensor, { foreignKey: 'sensor_id', as: 'sensor' });
  }
}

export default Measurement;
